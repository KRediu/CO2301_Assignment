#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LineOfSight.generated.h"

UCLASS(Blueprintable)
class CO2301_ASSIGNMENT_API UBTService_LineOfSight : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_LineOfSight();

private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
