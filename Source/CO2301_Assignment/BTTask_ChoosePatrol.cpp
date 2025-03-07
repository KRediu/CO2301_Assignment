#include "BTTask_ChoosePatrol.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"

UBTTask_ChoosePatrol::UBTTask_ChoosePatrol() { // set node name in BT
	NodeName = "Choose Patrol Point";
}

EBTNodeResult::Type UBTTask_ChoosePatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	PatrolPoint = ChooseWaypoint(); // call function and get a random patrol point

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	BlackboardComp->SetValueAsObject("PatrolPoint", PatrolPoint); // set it to blackboard key

    return EBTNodeResult::Succeeded;
}

AActor* UBTTask_ChoosePatrol::ChooseWaypoint()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints); // get all TargetPoint actors
	
	// pick one randomly from array
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Waypoints[index];
}