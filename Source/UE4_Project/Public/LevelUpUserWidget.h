// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpUserWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSkillLevelUpDelegate, ESkillType);
/**
 * 
 */
UCLASS()
class UE4_PROJECT_API ULevelUpUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class APlayerCharacter* PlayerCharacter;
public:
	FOnSkillLevelUpDelegate OnSkillLevelUp;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClick_Heal();
	UFUNCTION()
	void OnClick_Poison();

	void BindPlayerCharacter(class APlayerCharacter* NewPlayerCharacter);
};
