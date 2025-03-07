// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnemyAIController::BeginPlay() {

	Super::BeginPlay();

	// run enemy BT
	RunBehaviorTree(BT_PatrolMode);

	APawn* ControlledPawn = GetPawn();
	ACharacter* AICharacter = Cast<ACharacter>(ControlledPawn);
	AICharacter->GetCharacterMovement()->bOrientRotationToMovement = true; // ensure enemy looks towards movement direction
	AICharacter->GetCharacterMovement()->MaxWalkSpeed = 300.0f; // set speed
}

void AEnemyAIController::GameFinish() { // game end function for enemy, stop BT tree
	
	if (UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(GetBrainComponent()))
	{
		BTComponent->StopTree();
	}
}
