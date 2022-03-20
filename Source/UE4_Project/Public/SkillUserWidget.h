// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Blueprint/UserWidget.h"
#include "SkillUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API USkillUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	class UTextBlock* CoolTimeTextBlock;
	UPROPERTY()
	class UImage* LockImage;
	UPROPERTY()
	class UImage* SkillImage;

	UPROPERTY()
	TWeakObjectPtr<class USkillHolderComponent> SkillHolderComp;

	class UTexture2D* TextureHealSkill;
	class UTexture2D* TexturePoisonSkill;
public:
	virtual void NativeConstruct() override;

	void BindSkillHolder(class USkillHolderComponent* NewSkillHolderComp);

	UFUNCTION()
	void UpdateSkillState();

	UFUNCTION()
	void UpdateSkillGauge();
};
