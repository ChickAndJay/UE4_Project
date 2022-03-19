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

private:
	const float DamageOpacityDeacreasingSpeed = 0.035f;
	float CurrentOpacity;
	bool IsShowDamage = false;

	TWeakObjectPtr<class UMonsterStatComponent> MonsterStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UProgressBar* HPProgressBarMonster;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UTextBlock* DamageTextBlock;

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget(int reducedHP = 0);

public:
	void BindMonsterStat(class UMonsterStatComponent* MonsterStat);
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
