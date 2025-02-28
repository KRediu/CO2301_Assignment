// Copyright Epic Games, Inc. All Rights Reserved.


#include "CO2301_AssignmentGameModeBase.h"

void ACO2301_AssignmentGameModeBase::GameOver(bool Value)
{
	if (Value == true) {
		UE_LOG(LogTemp, Warning, TEXT("Victory Achieved"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You Died"));
	}
}

void ACO2301_AssignmentGameModeBase::BeginPlay()
{
	ACO2301_AssignmentGameModeBase::StartGame();
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &ACO2301_AssignmentGameModeBase::TimeUp, 60.0f);
}

void ACO2301_AssignmentGameModeBase::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Start"));
}

void ACO2301_AssignmentGameModeBase::TimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("Time is up"));
	GameOver(false);
}
