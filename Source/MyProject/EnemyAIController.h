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
class MYPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	//void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BT_PatrolMode;

protected:
	virtual void BeginPlay() override;

private:
	/*UPROPERTY()
	TArray<AActor*> Waypoints;

	AActor* ChooseWaypoint();

	void RandomPatrol();*/
};
