// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class AGun;
class ABullet;

UCLASS()
class CO2301_ASSIGNMENT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGun> GunClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> BulletClass;

	UPROPERTY(BlueprintReadOnly)
	bool IsDead = false;

	AGun* Gun;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* EnemyMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* EnemyGunMesh;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* EnemyBulletSpawnPoint;

	UPROPERTY(EditAnywhere)
	float Health = 100.0f;

	FTimerHandle DespawnTimer;

	void Fire();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
	
	void Death();
	void Despawn();
};
