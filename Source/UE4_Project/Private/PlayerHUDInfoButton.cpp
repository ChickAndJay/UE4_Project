// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDInfoButton.h"
#include "PlayerStatComponent.h"
#include "Components/TextBlock.h"

void UPlayerHUDInfoButton::NativeConstruct()
{
	LevelTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextSlot")));
}

void UPlayerHUDInfoButton::UpdatePlayerLevel(int NewLevel)
{
	
	FString NewLevelString = FString::FromInt(NewLevel);
	LevelTextBlock->SetText(FText::FromString(NewLevelString));
}
