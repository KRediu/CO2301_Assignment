// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
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
	UFUNCTION()
	void GameOver(bool Value);

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle EndGameTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void TimeUp();

	UPROPERTY(VisibleAnywhere)
	float GameDuration = 60.0f;
	
	

};
