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

protected:
	virtual void NativeConstruct() override;
public:
	void BindPlayerStat(class UPlayerStatComponent* NewPlayerStatComp);

	void UpdatePlayerHPStatus();
	UFUNCTION()
	void UpdatePlayerStaminaStatus();

	class UPlayerStatusBarWidget* HPBarWidget;
	class UPlayerStatusBarWidget* StaminaWidget;
};
