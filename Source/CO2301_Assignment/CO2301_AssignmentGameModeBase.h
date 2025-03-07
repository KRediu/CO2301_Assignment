// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "CO2301_AssignmentGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API ACO2301_AssignmentGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// game end functions
	UFUNCTION()
	void GameOver(bool Value);
	UFUNCTION()
	void Win();
	UFUNCTION()
	void Lose();

	// timer
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle EndGameTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// game end widgets/screens
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY()
	UUserWidget* WinScreen;
	UPROPERTY()
	UUserWidget* LossScreen;

	// game end sounds
	UPROPERTY(EditAnywhere)
	USoundBase* winSound;
	UPROPERTY(EditAnywhere)
	USoundBase* loseSound;

	// timer until game end screen display
	FTimerHandle ScreenTimer;
	
	// other gamemode functions
	void TimeUp();
	void RemoveHUD();

	// game timer duration
	UPROPERTY(VisibleAnywhere)
	float GameDuration = 60.0f;

};
