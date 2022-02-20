// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatusBarWidget.h"
#include "Components/ProgressBar.h"

void UPlayerStatusBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	StatusProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("StatusBar")));
	if (IsValid(StatusProgressBar))
		UpdateStatusWidget(1.0f);
}

void UPlayerStatusBarWidget::UpdateStatusWidget(float NewStatusValue)
{
	if (IsValid(StatusProgressBar))
		StatusProgressBar->SetPercent(NewStatusValue);;
}