// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

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
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* GunMesh;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BulletSpawnPoint;

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


	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	FTimerHandle JumpCooldown;

	void SetMoveAmount(float Value);
	void SetRotateAmount(float Value);
	void SetRotateYAmount(float Value);
	void SetStrafeAmount(float Value);
	void Jump();
	void JumpReset();
};
