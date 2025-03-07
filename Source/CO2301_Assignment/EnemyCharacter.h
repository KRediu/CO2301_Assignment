// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

// subclass forward declarations
class AGun;
class ABullet;

// enum class for win reason
UENUM(BlueprintType)
enum class EWinReason : uint8
{
	None UMETA(DisplayName = "None"),
	EnemyDeath UMETA(DisplayName = "ENEMY FELLED"),
};

UCLASS()
class CO2301_ASSIGNMENT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	// subclasses
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> BulletClass;

	// win reason
	UPROPERTY(BlueprintReadWrite)
	EWinReason WinReason = EWinReason::None;

	// actor variables
	UPROPERTY(BlueprintReadOnly)
	bool GameEnd = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health = 100.0f;

	AGun* Gun;

	// fire function
	void Fire();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// meshes and components
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* EnemyMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* EnemyGunMesh;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* EnemyBulletSpawnPoint;

	// sounds
	UPROPERTY(EditAnywhere)
	USoundBase* shootSound;
	UPROPERTY(EditAnywhere)
	USoundBase* deathSound;

	// despawn timer
	FTimerHandle DespawnTimer;

	// damage functions
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
	
	// death functions
	void Death();
	void Despawn();
};
