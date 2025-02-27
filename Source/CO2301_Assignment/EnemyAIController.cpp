// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/TargetPoint.h"

void AEnemyAIController::BeginPlay() {

	Super::BeginPlay();

	RunBehaviorTree(BT_PatrolMode);
	
	
	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(PlayerPawn);
	//MoveToActor(PlayerPawn, 10.0f);

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	//APawn* ControlledPawn = GetPawn();
	//if (ControlledPawn)
	//{
	//	ACharacter* AICharacter = Cast<ACharacter>(ControlledPawn);
	//	if (AICharacter)
	//	{
	//		AICharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	//		AICharacter->GetCharacterMovement()->MaxWalkSpeed = 300.0f; // Adjust speed here
	//		
	//	}
	//}

	//RandomPatrol();
}

//AActor* AEnemyAIController::ChooseWaypoint()
//{
//	int index = FMath::RandRange(0, Waypoints.Num() - 1);
//	return Waypoints[index];
//}
//
//void AEnemyAIController::RandomPatrol() 
//{
//	AActor* NextWaypoint = ChooseWaypoint();
//	
//	if (LineOfSightTo(NextWaypoint))
//	{
//		SetFocus(NextWaypoint);  // Look at waypoint if visible
//	}
//	else
//	{
//		ClearFocus(EAIFocusPriority::Gameplay); // Don't force look at waypoint
//	}
//
//	MoveToActor(NextWaypoint);
//}
//
//void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const
//	FPathFollowingResult& Result)
//{
//	Super::OnMoveCompleted(RequestID, Result);
//	RandomPatrol();
//}