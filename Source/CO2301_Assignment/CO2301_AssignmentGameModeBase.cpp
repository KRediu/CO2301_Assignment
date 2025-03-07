// Copyright Epic Games, Inc. All Rights Reserved.

#include "CO2301_AssignmentGameModeBase.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"

void ACO2301_AssignmentGameModeBase::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &ACO2301_AssignmentGameModeBase::TimeUp, GameDuration); // start game timer
}


void ACO2301_AssignmentGameModeBase::TimeUp() // out of time loss function
{
	// Get player character and set loss reason for screen
	AMyPlayerController* Controller = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	AMyCharacter* PlayerChar = Cast<AMyCharacter>(Controller->GetPawn());
	PlayerChar->LossReason = ELossReason::TimerUp;

	GameOver(false);
}

// Function removing the existing HUD widget
void ACO2301_AssignmentGameModeBase::RemoveHUD()
{
	AMyPlayerController* Controller = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->HUDWidget->RemoveFromViewport();
}

void ACO2301_AssignmentGameModeBase::GameOver(bool Value) // Game end function
{
	RemoveHUD();
	GetWorld()->GetTimerManager().PauseTimer(EndGameTimer); // Stop game timer

	if (Value) {
		UGameplayStatics::PlaySound2D(GetWorld(), winSound); // play win sound
		GetWorld()->GetTimerManager().SetTimer(ScreenTimer, this, &ACO2301_AssignmentGameModeBase::Win, 2.0f); // lose screen call
	}
	else
		GetWorld()->GetTimerManager().SetTimer(ScreenTimer, this, &ACO2301_AssignmentGameModeBase::Lose, 2.0f); // win screen call
}

void ACO2301_AssignmentGameModeBase::Win() // win function
{
	WinScreen = CreateWidget<UUserWidget>(GetWorld(), WinScreenClass);
	WinScreen->AddToViewport(); // add win screen to viewport
}

void ACO2301_AssignmentGameModeBase::Lose() // loss function
{
	LossScreen = CreateWidget<UUserWidget>(GetWorld(), LoseScreenClass);
	LossScreen->AddToViewport(); // add loss screen to viewport

	UGameplayStatics::PlaySound2D(GetWorld(), loseSound); // loss sound
}
