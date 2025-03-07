// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BT_PatrolMode;

	void GameFinish();

protected:
	virtual void BeginPlay() override;

};
