// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillUserWidget.h"
#include "SkillHolderComponent.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USkillUserWidget::NativeConstruct()
{
	CoolTimeTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("cool_time_text")));
	LockImage = Cast<UImage>(GetWidgetFromName(TEXT("lock_image")));
	SkillImage = Cast<UImage>(GetWidgetFromName(TEXT("skill_image")));

	CoolTimeTextBlock->SetVisibility(ESlateVisibility::Hidden);
	SkillImage->SetVisibility(ESlateVisibility::Hidden);
	LockImage->SetVisibility(ESlateVisibility::Visible);	

	FString FirstHealPath = FString("/Game/horror_grunge_gui/textures/icons/256/t_Aid_256.t_Aid_256");
	FString SecondPoisonPath = FString("/Game/horror_grunge_gui/textures/icons/256/t_Flame_256.t_Flame_256");

	TextureHealSkill = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FirstHealPath));
	TexturePoisonSkill = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SecondPoisonPath));
}

void USkillUserWidget::BindSkillHolder(USkillHolderComponent* NewSkillHolderComp)
{
	if (NewSkillHolderComp == nullptr)
		return;

	SkillHolderComp = NewSkillHolderComp;
	SkillHolderComp->OnSkillChange.AddUObject(this, &USkillUserWidget::UpdateSkillState);

	ESkillCategory skillCategory = static_cast<ESkillCategory>(SkillHolderComp->GetSkillCategory());
	if (skillCategory == ESkillCategory::Heal)
	{
		SkillImage->SetBrushFromTexture(TextureHealSkill);
	}
	else if (skillCategory == ESkillCategory::Poison)
	{
		SkillImage->SetBrushFromTexture(TexturePoisonSkill);
	}
}

void USkillUserWidget::UpdateSkillState()
{
	if (SkillHolderComp->IsAvailableSkillLevel())
	{
		if(!(SkillImage->IsVisible()))
			SkillImage->SetVisibility(ESlateVisibility::Visible);
		if(LockImage->IsVisible())
			LockImage->SetVisibility(ESlateVisibility::Hidden);

		if (SkillHolderComp->IsAvailableCoolTime())
		{
			if(CoolTimeTextBlock->IsVisible())
				CoolTimeTextBlock->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			if (!CoolTimeTextBlock->IsVisible())
				CoolTimeTextBlock->SetVisibility(ESlateVisibility::Visible);

			FString coolTimeText = FString::Printf(TEXT("%d"), (int)SkillHolderComp->GetCurrentCoolTime());
			CoolTimeTextBlock->SetText(FText::FromString(coolTimeText));
		}
	}
	else
	{
		if ((SkillImage->IsVisible()))
			SkillImage->SetVisibility(ESlateVisibility::Hidden);
		if (!LockImage->IsVisible())
			LockImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void USkillUserWidget::UpdateSkillGauge()
{
}

