// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class AGun;
class ABullet;

UCLASS()
class CO2301_ASSIGNMENT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> BulletClass;

	UPROPERTY(BlueprintReadOnly)
	bool IsDead = false;
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
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* CharMesh;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BulletSpawnPoint;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	float DeltaLocation = 0;
	float DeltaLocationZ = 0;
	float DeltaRotation = 0;
	float DeltaRotationY = 0;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 50.0f;
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100.0f;
	UPROPERTY(EditAnywhere)
	float StrafeSpeed = 50.0f;

	bool IsJumping = false;

	FTimerHandle JumpCooldown;
	FTimerHandle ReloadTimer;
	FTimerHandle DespawnTimer;

	void SetMoveAmount(float Value);
	void SetRotateAmount(float Value);
	void SetRotateYAmount(float Value);
	void SetStrafeAmount(float Value);
	void Jump();
	void JumpReset();

	void Fire();
	void Reload();
	void ReloadReset();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	void Death();
	void Despawn();
};
