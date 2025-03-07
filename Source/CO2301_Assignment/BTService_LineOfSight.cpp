#include "BTService_LineOfSight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"

UBTService_LineOfSight::UBTService_LineOfSight()
{
    // set the interval
    bCreateNodeInstance = true;
}

void UBTService_LineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // get enemy character
    AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    APawn* AICharacter = AIController->GetPawn();

    // get player character
    AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(AIController->GetWorld(), 0));  // Assumes player is at index 0

    bool bLineOfSight = false; // LOS variable

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

    // update values accordingly
    if (AIController->LineOfSightTo(PlayerCharacter)) {
        bLineOfSight = true;
        Blackboard->SetValueAsBool("LineOfSight", bLineOfSight);
    }
    else {
        bLineOfSight = false;
        Blackboard->ClearValue("LineOfSight");
    }
        


    
        
}