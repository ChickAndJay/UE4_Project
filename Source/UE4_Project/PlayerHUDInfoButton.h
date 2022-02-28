// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDInfoButton.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UPlayerHUDInfoButton : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UTextBlock* LevelTextBlock;

public:
	virtual void NativeConstruct() override;

	void UpdatePlayerLevel(int NewLevel);
};
