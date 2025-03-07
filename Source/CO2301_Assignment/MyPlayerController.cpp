// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyCharacter.h"

AMyPlayerController::AMyPlayerController() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

	// create start screen on launch
	StartScreen = CreateWidget<UUserWidget>(GetWorld(), StartScreenClass);
	StartScreen->AddToViewport();
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	if (!bHasPressedKey)
	{
		HandleKeyPress(); // check if any key is pressed
	}
}

void AMyPlayerController::HandleKeyPress()
{
	if (IsInputKeyDown(EKeys::AnyKey))  // This checks any key press
	{
		// remove the start screen
		StartScreen->RemoveFromViewport();
		bHasPressedKey = true;

		AMyCharacter* PlayerChar = Cast<AMyCharacter>(GetPawn());
		PlayerChar->GameStart = true; // enable movement and actions for player

		// place HUD on screen
		HUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		HUDWidget->AddToViewport();

		// stop checking every tick
		PrimaryActorTick.bCanEverTick = false;
	}
}