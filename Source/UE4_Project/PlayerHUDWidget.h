// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	TWeakObjectPtr<class UPlayerStatComponent> PlayerStatComp;

	UPROPERTY()
	class UPlayerStatusBarWidget* HPBarWidget;
	UPROPERTY()
	class UPlayerStatusBarWidget* StaminaWidget;

	UPROPERTY()
	class UTextBlock* HPTextBlock;
	UPROPERTY()
	class UTextBlock* StaminaTextBlock;
protected:
	virtual void NativeConstruct() override;
public:
	void BindPlayerStat(class UPlayerStatComponent* NewPlayerStatComp);

	UFUNCTION()
	void UpdatePlayerHPStatus();
	UFUNCTION()
	void UpdatePlayerStaminaStatus();
};
