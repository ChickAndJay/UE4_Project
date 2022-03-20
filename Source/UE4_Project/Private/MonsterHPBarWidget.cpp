// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHPBarWidget.h"
#include "MonsterStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Styling/SlateColor.h"
#include "Math/Color.h"

void UMonsterHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentOpacity = 0.f;

	HPProgressBarMonster = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPProgressBar")));
	if (IsValid(HPProgressBarMonster))
	{
		MYLOG(TEXT("HP Bar is valid"));
		UpdateHPWidget();
	}
	else
	{
		MYLOG(TEXT("HP Bar is Fail"));
	}

	DamageTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));
	if (DamageTextBlock != nullptr)
	{
		FSlateColor color(FLinearColor(1.0f, 1.0f, 1.0f, CurrentOpacity));
		DamageTextBlock->SetColorAndOpacity(color);
	}

	IsShowDamage = false;

	MYLOG_S();
}

void UMonsterHPBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsShowDamage)
	{
		CurrentOpacity -= DamageOpacityDeacreasingSpeed;
		
		if (CurrentOpacity <= 0)
		{
			IsShowDamage = false;
			CurrentOpacity = 0.f;
		}
		FSlateColor color(FLinearColor(1.0f, 1.0f, 1.0f, CurrentOpacity));
		DamageTextBlock->SetColorAndOpacity(color);
	}
}

void UMonsterHPBarWidget::UpdateHPWidget(int reducedHP)
{
	HPProgressBarMonster->SetPercent(MonsterStat->GetHPRatio());

	if (reducedHP > 0)
	{
		CurrentOpacity = 1.0f;

		FString damageText = FString::Printf(TEXT("%d"), reducedHP);
		DamageTextBlock->SetText(FText::FromString(damageText));

		FSlateColor color(FLinearColor(1.0f, 1.0f, 1.0f, CurrentOpacity));
		DamageTextBlock->SetColorAndOpacity(color);

		IsShowDamage = true;
	}
}

void UMonsterHPBarWidget::BindMonsterStat(UMonsterStatComponent* NewMonsterStat)
{
	MYLOG_S();
	if (NewMonsterStat == nullptr) 
	{
		MYLOG(TEXT("Fail"));
		return;
	}

	MonsterStat = NewMonsterStat;
	MonsterStat->OnHPChanged.AddUObject(this, &UMonsterHPBarWidget::UpdateHPWidget);
}
