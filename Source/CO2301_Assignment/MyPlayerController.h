// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CO2301_ASSIGNMENT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AMyPlayerController();

    UPROPERTY()
    UUserWidget* HUDWidget;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditAnywhere)
    TSubclassOf<class UUserWidget> HUDWidgetClass;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class UUserWidget> StartScreenClass;

    UPROPERTY()
    UUserWidget* StartScreen;

    bool bHasPressedKey = false;

    void HandleKeyPress();
};
