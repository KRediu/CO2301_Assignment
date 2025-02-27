// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class AGun;

UCLASS()
class CO2301_ASSIGNMENT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;

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
	USkeletalMeshComponent* EnemyMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* EnemyGunMesh;
};
