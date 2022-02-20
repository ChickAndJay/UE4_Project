// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "PlayerStatusBarWidget.h"
#include "PlayerStatComponent.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBarWidget = Cast<UPlayerStatusBarWidget>(GetWidgetFromName(TEXT("PlayerHPBar")));
	StaminaWidget = Cast<UPlayerStatusBarWidget>(GetWidgetFromName(TEXT("PlayerStaminaBar")));
}

void UPlayerHUDWidget::BindPlayerStat(UPlayerStatComponent* NewPlayerStatComp)
{
	if (NewPlayerStatComp != nullptr)
	{
		PlayerStatComp = NewPlayerStatComp;
	}
}

void UPlayerHUDWidget::UpdatePlayerHPStatus()
{
	if (IsValid(HPBarWidget) && PlayerStatComp.IsValid())
	{		
		HPBarWidget->UpdateStatusWidget(PlayerStatComp->GetHPRatio());
	}
}

void UPlayerHUDWidget::UpdatePlayerStaminaStatus()
{
	if (IsValid(StaminaWidget) && PlayerStatComp.IsValid())
	{
		StaminaWidget->UpdateStatusWidget(PlayerStatComp->GetStaminaRatio());
	}
}
