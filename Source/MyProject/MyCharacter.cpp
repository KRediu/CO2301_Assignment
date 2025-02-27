// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

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
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.0f;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->CameraRotationLagSpeed = 5.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Attachment"));
	GunMesh->SetupAttachment(CharMesh, "gun_socket");

	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet"));
	BulletSpawnPoint->SetupAttachment(GunMesh);

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
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddControllerPitchInput(DeltaRotationY);
	AddControllerYawInput(DeltaRotation);
	AddMovementInput(GetActorForwardVector(), DeltaLocation);
	AddMovementInput(GetActorRightVector(), DeltaLocationZ);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move", this, &AMyCharacter::SetMoveAmount);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::SetRotateAmount);
	PlayerInputComponent->BindAxis("Strafe", this, &AMyCharacter::SetStrafeAmount);
	PlayerInputComponent->BindAxis("Look Up", this, &AMyCharacter::SetRotateYAmount);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
}

void AMyCharacter::SetMoveAmount(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Drive Value: %f"), Value);
	DeltaLocation = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;
}

void AMyCharacter::SetStrafeAmount(float Value)
{
	DeltaLocationZ = Value * StrafeSpeed * GetWorld()->DeltaTimeSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("Strafe Value: %f"), Value);
}

void AMyCharacter::SetRotateAmount(float Value)
{
	DeltaRotation = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("Rotate Value: %f"), Value);
}


void AMyCharacter::SetRotateYAmount(float Value)
{
	DeltaRotationY = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("Rotate Value: %f"), Value);
}


void AMyCharacter::Jump() 
{
	bPressedJump = true;
	GetWorld()->GetTimerManager().SetTimer(JumpCooldown, this, &AMyCharacter::JumpReset, 1.0f);
}


void AMyCharacter::JumpReset() 
{
	bPressedJump = false;
}