// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Bullet.h"
#include "Gun.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Char Mesh"));
	CharMesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(CharMesh);
	SpringArm->SetRelativeLocation(FVector(0.0f, 90.0f, 40.0f));
	SpringArm->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet"));
	BulletSpawnPoint->SetupAttachment(CharMesh);
	BulletSpawnPoint->SetRelativeLocation(FVector(60.0f, 20.0f, 24.0f));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->PlayerCameraManager->ViewPitchMin = -40.0f; // Look down limit
		PlayerController->PlayerCameraManager->ViewPitchMax = 40.0f;  // Look up limit
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	if (Gun) {
		Gun->AttachToCharacter(this);
		Gun->SetActorEnableCollision(false);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead) { // Rotation call using below rotation value functions
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

	// Action calls - jump, fire, reload
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Fire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyCharacter::Reload);
}

// Forward/backward movement value update
void AMyCharacter::SetMoveAmount(float Value)
{
	if (!IsDead)
		DeltaLocation = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;
}

// Left/right movement value update
void AMyCharacter::SetStrafeAmount(float Value)
{
	if (!IsDead)
		DeltaLocationZ = Value * StrafeSpeed * GetWorld()->DeltaTimeSeconds;
}

// X-axis rotation value update
void AMyCharacter::SetRotateAmount(float Value)
{
	if (!IsDead)
		DeltaRotation = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
}

// Y-axis rotation value update
void AMyCharacter::SetRotateYAmount(float Value)
{
	if(!IsDead)
		DeltaRotationY = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
}

// Jumping function
void AMyCharacter::Jump() 
{
	if (!IsDead && !IsReloading) { // prevents jump during reload and after death
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
	if(Ammo > 0 && !IsReloading && !IsDead && !IsJumping){ // can't shoot with no ammo and while reloading, jumping or dead
		if (BulletClass) { // checks bullet projectile has been set in the editor

			FVector SpawnLocation = BulletSpawnPoint->GetComponentLocation();
			FRotator SpawnRotation = BulletSpawnPoint->GetComponentRotation();
			ABullet* TempBullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation); // spawns bullet subclass using above variables
			
			TempBullet->SetOwner(this); // set actor as owner
			TempBullet->OwnerCollisionPrevention(); // prevents collision with owner
			TempBullet->SetActorRelativeScale3D(FVector(0.075f, 0.075f, 0.075f)); // scales shape to bullet size

			/*UGameplayStatics::PlaySound2D(GetWorld(), thunk);*/
		}
		Ammo--;
		UE_LOG(LogTemp, Warning, TEXT("Firing!"))
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Out of Ammo - Reload!"))
}

void AMyCharacter::Reload() 
{
	if (!IsReloading && !IsDead && !IsJumping) {
		UE_LOG(LogTemp, Warning, TEXT("Reloading!"));
		IsReloading = true;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &AMyCharacter::ReloadReset, 3.17f);
	}
}

void AMyCharacter::ReloadReset() {
	Ammo = InitialAmmo;
	IsReloading = false;
}

float AMyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsDead) {
		UE_LOG(LogTemp, Warning, TEXT("Damage to player: %f"), DamageAmount);

		Health -= DamageAmount;
		if (Health <= 0)
			AMyCharacter::Death();

		return DamageAmount;
	}
	return 0;
}

void AMyCharacter::Death() 
{
	UE_LOG(LogTemp, Warning, TEXT("You have been slain"));
	IsDead = true;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->SetRelativeLocation(FVector(-80.0f, 0.0f, 70.0f));
	SpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	GetWorld()->GetTimerManager().SetTimer(DespawnTimer, this, &AMyCharacter::Despawn, 15.0f);
}

void AMyCharacter::Despawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Player despawned"));
	CharMesh->SetAnimInstanceClass(nullptr);
	Destroy();
	Gun->Destroy();
}
