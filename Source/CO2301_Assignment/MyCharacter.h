// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

// subclass forward declarations
class AGun;
class ABullet;

// enum class for loss reason
UENUM(BlueprintType)
enum class ELossReason : uint8
{
	None UMETA(DisplayName = "None"),
	Suicide UMETA(DisplayName = "Goodbye, cruel world!"),
	HealthDepleted UMETA(DisplayName = "YOU DIED"),
	TimerUp UMETA(DisplayName = "OUT OF TIME")
};

UCLASS()
class CO2301_ASSIGNMENT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// subclasses
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> BulletClass;

	// loss reason declaration
	UPROPERTY(BlueprintReadWrite)
	ELossReason LossReason = ELossReason::None;

	// actor variables
	UPROPERTY(BlueprintReadOnly)
	bool GameStart = false;
	UPROPERTY(BlueprintReadOnly)
	bool GameEnd = false;
	UPROPERTY(BlueprintReadOnly)
	bool IsReloading = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int InitialAmmo = 30;
	UPROPERTY(BlueprintReadOnly)
	int Ammo = InitialAmmo;

	AGun* Gun;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// actor mesh and components
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* CharMesh;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BulletSpawnPoint;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	// sounds
	UPROPERTY(EditAnywhere)
	USoundBase* shootSound;
	UPROPERTY(EditAnywhere)
	USoundBase* deathSound;

	// movement values
	float DeltaLocation = 0;
	float DeltaLocationZ = 0;
	float DeltaRotation = 0;
	float DeltaRotationY = 0;

	// movement variables
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 50.0f;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100.0f;
	UPROPERTY(EditAnywhere)
	float StrafeSpeed = 50.0f;

	// bool to prevent certain actions
	bool IsJumping = false;

	// timers
	FTimerHandle JumpCooldown;
	FTimerHandle ReloadTimer;

	// movement functions
	void SetMoveAmount(float Value);
	void SetRotateAmount(float Value);
	void SetRotateYAmount(float Value);
	void SetStrafeAmount(float Value);
	void Jump();
	void JumpReset();

	// firing actions
	void Fire();
	void Reload();
	void ReloadReset();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	// death functions
	void Death();
	void Suicide();

	// quit function
	void QuitGame();
};
