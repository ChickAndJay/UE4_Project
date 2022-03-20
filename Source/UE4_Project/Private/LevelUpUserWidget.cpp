// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpUserWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

void ULevelUpUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UUserWidget* HealButtonWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("heal_level_up")));
	UUserWidget* PoisonButtonWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("poison_level_up")));

	UButton* HealButton = Cast<UButton>(HealButtonWidget->GetWidgetFromName(TEXT("up_button")));
	UButton* PoisonButton = Cast<UButton>(PoisonButtonWidget->GetWidgetFromName(TEXT("up_button")));

	UImage* HealSkillImage = Cast<UImage>(HealButtonWidget->GetWidgetFromName(TEXT("skill_image")));
	UImage* PoisonSkillImage = Cast<UImage>(PoisonButtonWidget->GetWidgetFromName(TEXT("skill_image")));

	HealButton->OnClicked.AddDynamic(this, &ULevelUpUserWidget::OnClick_Heal);
	PoisonButton->OnClicked.AddDynamic(this, &ULevelUpUserWidget::OnClick_Poison);

	FString FirstHealPath = FString("/Game/horror_grunge_gui/textures/icons/256/t_Aid_256.t_Aid_256");
	FString SecondPoisonPath = FString("/Game/horror_grunge_gui/textures/icons/256/t_Flame_256.t_Flame_256");

	UTexture2D* TextureHealSkill = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FirstHealPath));
	UTexture2D* TexturePoisonSkill = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *SecondPoisonPath));

	HealSkillImage->SetBrushFromTexture(TextureHealSkill);
	PoisonSkillImage->SetBrushFromTexture(TexturePoisonSkill);
}

void ULevelUpUserWidget::OnClick_Heal()
{
	RemoveFromParent();

	OnSkillLevelUp.Broadcast(ESkillType::FIRST);	
}

void ULevelUpUserWidget::OnClick_Poison()
{
	RemoveFromParent();

	OnSkillLevelUp.Broadcast(ESkillType::SECOND);
}

void ULevelUpUserWidget::BindPlayerCharacter(APlayerCharacter* NewPlayerCharacter)
{
	PlayerCharacter = NewPlayerCharacter;
}
