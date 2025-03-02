// Copyright Epic Games, Inc. All Rights Reserved.

#include "CO2301_AssignmentGameModeBase.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"

void ACO2301_AssignmentGameModeBase::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &ACO2301_AssignmentGameModeBase::TimeUp, GameDuration);
}


void ACO2301_AssignmentGameModeBase::TimeUp()
{
	AMyPlayerController* Controller = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (Controller)
	{
		AMyCharacter* PlayerChar = Cast<AMyCharacter>(Controller->GetPawn());
		if (PlayerChar)
		{
			PlayerChar->LossReason = ELossReason::TimerUp;
		}
	}
	GameOver(false);
}

// Function removing the existing HUD widget
void ACO2301_AssignmentGameModeBase::RemoveHUD()
{
	AMyPlayerController* Controller = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (Controller)
	{
		if (Controller->HUDWidget)
		{
			Controller->HUDWidget->RemoveFromViewport();
		}
	}
}

void ACO2301_AssignmentGameModeBase::GameOver(bool Value)
{
	RemoveHUD();
	GetWorld()->GetTimerManager().PauseTimer(EndGameTimer);

	if (Value)
		GetWorld()->GetTimerManager().SetTimer(ScreenTimer, this, &ACO2301_AssignmentGameModeBase::Win, 2.0f);
	else
		GetWorld()->GetTimerManager().SetTimer(ScreenTimer, this, &ACO2301_AssignmentGameModeBase::Lose, 2.0f);
}

void ACO2301_AssignmentGameModeBase::Win()
{
	if (WinScreenClass)
	{
		WinScreen = CreateWidget<UUserWidget>(GetWorld(), WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
}

void ACO2301_AssignmentGameModeBase::Lose()
{
	if (LoseScreenClass)
	{
		LossScreen = CreateWidget<UUserWidget>(GetWorld(), LoseScreenClass);
		if (LossScreen)
		{
			LossScreen->AddToViewport();
		}
	}
}
