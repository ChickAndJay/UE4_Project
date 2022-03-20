// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "PlayerStatusBarWidget.h"
#include "PlayerHUDInfoButton.h"
#include "PlayerStatComponent.h"
#include "Components/TextBlock.h"
#include "SkillUserWidget.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBarWidget = Cast<UPlayerStatusBarWidget>(GetWidgetFromName(TEXT("PlayerHPBar")));
	StaminaWidget = Cast<UPlayerStatusBarWidget>(GetWidgetFromName(TEXT("PlayerStaminaBar")));
	ExpWidget = Cast<UPlayerStatusBarWidget>(GetWidgetFromName(TEXT("PlayerExp")));

	InfoButtonWidget = Cast<UPlayerHUDInfoButton>(GetWidgetFromName(TEXT("HUDInfoButton")));

	HPTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));
	StaminaTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("StaminaText")));

	int firstSkillIdx = static_cast<int>(ESkillType::FIRST);
	int secondSkillIdx = static_cast<int>(ESkillType::SECOND);
	
	SkillWidgetArr[firstSkillIdx] = Cast<USkillUserWidget>(GetWidgetFromName(TEXT("Skill_1")));
	SkillWidgetArr[secondSkillIdx] = Cast<USkillUserWidget>(GetWidgetFromName(TEXT("Skill_2")));
}

void UPlayerHUDWidget::BindPlayerStat(UPlayerStatComponent* NewPlayerStatComp)
{
	if (NewPlayerStatComp != nullptr)
	{
		PlayerStatComp = NewPlayerStatComp;

		int firstSkillIdx = static_cast<int>(ESkillType::FIRST);
		int secondSkillIdx = static_cast<int>(ESkillType::SECOND);

		SkillWidgetArr[firstSkillIdx]->BindSkillHolder(PlayerStatComp->GetSkillHolderComp(ESkillType::FIRST));
		SkillWidgetArr[secondSkillIdx]->BindSkillHolder(PlayerStatComp->GetSkillHolderComp(ESkillType::SECOND));

		SkillWidgetArr[firstSkillIdx]->UpdateSkillState();
		SkillWidgetArr[secondSkillIdx]->UpdateSkillState();
	}
}

void UPlayerHUDWidget::UpdatePlayerStatus()
{
	UpdatePlayerHPStatus();
	UpdatePlayerExpStatus();
	UpdatePlayerHUDInfo();
	UpdatePlayerStaminaStatus();
	UpdatePlayerSkills();
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

void UPlayerHUDWidget::UpdatePlayerExpStatus()
{
	if (IsValid(ExpWidget) && PlayerStatComp.IsValid())
	{
		ExpWidget->UpdateStatusWidget(PlayerStatComp->GetExpRatio());
	}
}

void UPlayerHUDWidget::UpdatePlayerHUDInfo()
{
	if (IsValid(InfoButtonWidget) && PlayerStatComp.IsValid())
	{
		InfoButtonWidget->UpdatePlayerLevel(PlayerStatComp->GetCurrentLevel());
	}
}

void UPlayerHUDWidget::UpdatePlayerSkills()
{
	int firstSkillIdx = static_cast<int>(ESkillType::FIRST);
	int secondSkillIdx = static_cast<int>(ESkillType::SECOND);

	SkillWidgetArr[firstSkillIdx]->UpdateSkillState();
	SkillWidgetArr[secondSkillIdx]->UpdateSkillState();
}