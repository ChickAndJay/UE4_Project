// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "PlayerStatusBarWidget.h"
#include "PlayerStatComponent.h"
#include "Components/TextBlock.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBarWidget = Cast<UPlayerStatusBarWidget>(GetWidgetFromName(TEXT("PlayerHPBar")));
	StaminaWidget = Cast<UPlayerStatusBarWidget>(GetWidgetFromName(TEXT("PlayerStaminaBar")));

	HPTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));
	StaminaTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("StaminaText")));
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

		FString hpText = FString::Printf(TEXT("%d / %d"), PlayerStatComp->GetCurrentHP(), PlayerStatComp->GetMaxHP());

		HPTextBlock->SetText(FText::FromString(hpText));
	}
}

void UPlayerHUDWidget::UpdatePlayerStaminaStatus()
{
	if (IsValid(StaminaWidget) && PlayerStatComp.IsValid())
	{
		StaminaWidget->UpdateStatusWidget(PlayerStatComp->GetStaminaRatio());

		FString stminaText = FString::Printf(TEXT("%d / %d"), (int)PlayerStatComp->GetCurrentStamina(), (int)PlayerStatComp->GetMaxStamina());
		StaminaTextBlock->SetText(FText::FromString(stminaText));
	}
}
