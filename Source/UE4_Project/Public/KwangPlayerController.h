// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KwangPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API AKwangPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AKwangPlayerController();

	void ChangeInputMode(bool GameMode);
protected:	
	virtual void BeginPlay() override;

public:
	class UPlayerHUDWidget* GetPlayerHUDWidget();

protected:
	UPROPERTY()
	TSubclassOf<class UPlayerHUDWidget> PlayerHUDWidgetClass;
private:
	UPROPERTY()
	class UPlayerHUDWidget* PlayerHUDWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
};
