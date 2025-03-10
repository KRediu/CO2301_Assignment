// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChoosePatrol.generated.h"


UCLASS(Blueprintable)
class CO2301_ASSIGNMENT_API UBTTask_ChoosePatrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ChoosePatrol();

	UPROPERTY() 
	TArray<AActor*> Waypoints; // targetpoint array

	AActor* PatrolPoint;

	AActor* ChooseWaypoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
