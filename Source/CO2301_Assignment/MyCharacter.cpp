// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "CO2301_AssignmentGameModeBase.h"
#include "Bullet.h"
#include "Gun.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// create player mesh
	CharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Char Mesh"));
	CharMesh->SetupAttachment(RootComponent);

	// create spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(CharMesh);
	SpringArm->SetRelativeLocation(FVector(0.0f, 90.0f, 40.0f));
	SpringArm->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// create camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	// create bullet spawnpoint
	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet"));
	BulletSpawnPoint->SetupAttachment(CharMesh);
	BulletSpawnPoint->SetRelativeLocation(FVector(60.0f, 20.0f, 24.0f));

	// autopossess player on launch
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// camera view limitations on y axis
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->PlayerCameraManager->ViewPitchMin = -40.0f; // Look down limit
	PlayerController->PlayerCameraManager->ViewPitchMax = 40.0f;  // Look up limit

	// spawn gun, attach to actor, prevent collisions
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToCharacter(this);
	Gun->SetActorEnableCollision(false);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameStart && !GameEnd) { // Rotation call using below rotation value functions
		AddControllerPitchInput(DeltaRotationY);
		AddControllerYawInput(DeltaRotation);
		
		if (!IsReloading) { // Movement call using below movement value functions
			AddMovementInput(GetActorForwardVector(), DeltaLocation);
			AddMovementInput(GetActorRightVector(), DeltaLocationZ);
		}
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis calls - movement/rotation
	PlayerInputComponent->BindAxis("Move", this, &AMyCharacter::SetMoveAmount);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::SetRotateAmount);
	PlayerInputComponent->BindAxis("Strafe", this, &AMyCharacter::SetStrafeAmount);
	PlayerInputComponent->BindAxis("Look Up", this, &AMyCharacter::SetRotateYAmount);

	// Action calls - jump, fire, etc.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Fire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyCharacter::Reload);
	PlayerInputComponent->BindAction("Suicide", IE_Pressed, this, &AMyCharacter::Suicide);
	PlayerInputComponent->BindAction("Quit", IE_Pressed, this, &AMyCharacter::QuitGame);
}

// Forward/backward movement value update
void AMyCharacter::SetMoveAmount(float Value)
{
	if (GameStart && !GameEnd)
		DeltaLocation = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;
}

// Left/right movement value update
void AMyCharacter::SetStrafeAmount(float Value)
{
	if (GameStart && !GameEnd)
		DeltaLocationZ = Value * StrafeSpeed * GetWorld()->DeltaTimeSeconds;
}

// X-axis rotation value update
void AMyCharacter::SetRotateAmount(float Value)
{
	if (GameStart && !GameEnd)
		DeltaRotation = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
}

// Y-axis rotation value update
void AMyCharacter::SetRotateYAmount(float Value)
{
	if(GameStart && !GameEnd)
		DeltaRotationY = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
}

// Jumping function
void AMyCharacter::Jump() 
{
	if (GameStart && !GameEnd && !IsReloading) { // prevents jump during reload and after death
		bPressedJump = true; // built-in variable enabling the character to jump
		IsJumping = true; // unique bool variable made to limit other actions during air-time
		GetWorld()->GetTimerManager().SetTimer(JumpCooldown, this, &AMyCharacter::JumpReset, 1.0f); // calls reset function after a timer
	}
}

// Jump reset function
void AMyCharacter::JumpReset() 
{
	bPressedJump = false; // confirms that built-in jump is finished to allow another
	IsJumping = false;
}

// Shooting/bullet spawning function
void AMyCharacter::Fire()
{
	if(Ammo > 0 && !IsReloading && GameStart && !GameEnd && !IsJumping){ // can't shoot with no ammo and while reloading, jumping or dead
		if (BulletClass) { // checks bullet projectile has been set in the editor

			FVector SpawnLocation = BulletSpawnPoint->GetComponentLocation();
			FRotator SpawnRotation = BulletSpawnPoint->GetComponentRotation();
			ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation); // spawns bullet subclass using above variables
			
			TempBullet->SetOwner(this); // set actor as owner
			TempBullet->OwnerCollisionPrevention(); // prevents collision with owner
			TempBullet->SetActorRelativeScale3D(FVector(0.075f, 0.075f, 0.075f)); // scales shape to bullet size

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), shootSound, GetActorLocation());
		}
		Ammo--;
	}
}

void AMyCharacter::Reload() // player reload
{
	if (!IsReloading && GameStart && !GameEnd && !IsJumping) { // prevented by other actions/states
		IsReloading = true; // prevents other actions/states
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AMyCharacter::ReloadReset, 3.17f); // call reload finish after a timer
	}
}

void AMyCharacter::ReloadReset() { // refill player ammo and finish process
	Ammo = InitialAmmo;
	IsReloading = false;
}

float AMyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	if (GameStart && !GameEnd) { // applies only if game is active
		UE_LOG(LogTemp, Warning, TEXT("Damage to player: %f"), DamageAmount);

		Health -= DamageAmount;
		if (Health <= 0) 
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), deathSound, GetActorLocation());
			LossReason = ELossReason::HealthDepleted;
			Death();
		}

		return DamageAmount;
	}
	return 0;
}

// Function simulating death
void AMyCharacter::Death() 
{
	GameEnd = true; // enables game end condition

	SpringArm->bUsePawnControlRotation = false; // sets the camera in a top view (gta style, but I can't be bothered to do the slow turning)
	SpringArm->SetRelativeLocation(FVector(-80.0f, 0.0f, 70.0f));
	SpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	ACO2301_AssignmentGameModeBase* GameMode = Cast<ACO2301_AssignmentGameModeBase>(UGameplayStatics::GetGameMode(this)); // pauses end timer to prevent other actions upon loss
	GameMode->GameOver(false); // call game end function
}

// debug function - kills character immediately
void AMyCharacter::Suicide() 
{
	Health = 0;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), deathSound, GetActorLocation());
	LossReason = ELossReason::Suicide;
	Death();
}


void AMyCharacter::QuitGame() // quit with esc
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
