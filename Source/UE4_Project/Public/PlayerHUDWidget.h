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
	class UPlayerStatusBarWidget* ExpWidget;
	UPROPERTY()
	class UPlayerHUDInfoButton* InfoButtonWidget;

	UPROPERTY()
	class UTextBlock* HPTextBlock;
	UPROPERTY()
	class UTextBlock* StaminaTextBlock;
	UPROPERTY()
	class USkillUserWidget* SkillWidgetArr[2];
protected:
	virtual void NativeConstruct() override;
public:
	void BindPlayerStat(class UPlayerStatComponent* NewPlayerStatComp);

	UFUNCTION()
	void UpdatePlayerStatus();
	UFUNCTION()
	void UpdatePlayerHPStatus();
	UFUNCTION()
	void UpdatePlayerStaminaStatus();
	UFUNCTION()
	void UpdatePlayerExpStatus();
	UFUNCTION()
	void UpdatePlayerHUDInfo();
	UFUNCTION()
	void UpdatePlayerSkills();
};
