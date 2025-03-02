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

	if (StartScreenClass)
	{
		StartScreen = CreateWidget<UUserWidget>(GetWorld(), StartScreenClass);
		if (StartScreen)
		{
			StartScreen->AddToViewport();
		}
	}
}

void AMyPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	if (!bHasPressedKey)
	{
		// Check if any key is pressed
		HandleKeyPress();
	}
}

void AMyPlayerController::HandleKeyPress()
{
	if (IsInputKeyDown(EKeys::AnyKey))  // This checks any key press
	{
		// Remove the start screen widget
		if (StartScreen)
		{
			StartScreen->RemoveFromViewport();
			bHasPressedKey = true;
		}
		AMyCharacter* PlayerChar = Cast<AMyCharacter>(GetPawn());
		if (PlayerChar)
		{
			PlayerChar->GameStart = true;
		}

		if (HUDWidgetClass)
		{
			HUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass);
			if (HUDWidget)
			{
				HUDWidget->AddToViewport();
			}
		}
		PrimaryActorTick.bCanEverTick = false;
	}
}