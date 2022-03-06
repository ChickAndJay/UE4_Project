// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHPBarWidget.h"
#include "MonsterStatComponent.h"
#include "Components/ProgressBar.h"

void UMonsterHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBarMonster = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPProgressBar")));
	if (IsValid(HPProgressBarMonster))
		UpdateHPWidget();
}

void UMonsterHPBarWidget::UpdateHPWidget()
{
	HPProgressBarMonster->SetPercent(MonsterStat->GetHPRatio());
}

void UMonsterHPBarWidget::BindMonsterStat(UMonsterStatComponent* NewMonsterStat)
{
	if (NewMonsterStat == nullptr)
		return;

	MonsterStat = NewMonsterStat;
	MonsterStat->OnHPChanged.AddUObject(this, &UMonsterHPBarWidget::UpdateHPWidget);
}
