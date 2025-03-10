// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class AMyCharacter;
class AEnemyCharacter;

UCLASS()
class CO2301_ASSIGNMENT_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* GunMesh;

	void AttachToCharacter(AMyCharacter* MyCharacter);
	void AttachToEnemy(AEnemyCharacter* EnemyCharacter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
