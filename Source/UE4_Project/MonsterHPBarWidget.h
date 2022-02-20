// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UMonsterHPBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

public:
	void BindMonsterStat(class UMonsterStatComponent* MonsterStat);

private:
	TWeakObjectPtr<class UMonsterStatComponent> MonsterStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UProgressBar* HPProgressBarMonster;
};
