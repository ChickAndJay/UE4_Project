// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleMenuPlayerController.h"
#include "TitleMenuWidget.h"

ATitleMenuPlayerController::ATitleMenuPlayerController()
{
	static ConstructorHelpers::FClassFinder<UTitleMenuWidget> TITLE_WIDGET_C(TEXT("/Game/CustomContent/UI/TitleMenu.TitleMenu_C"));
	if (TITLE_WIDGET_C.Succeeded())
	{
		MYLOG(TEXT("Succeeded"));
		TitleMenuWidgetClass = TITLE_WIDGET_C.Class;
	}
	else
	{
		MYLOG(TEXT("FAIL"));
	}

	bEnableClickEvents = true;
	bShowMouseCursor = true;
}

void ATitleMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TitleMenuWidget = CreateWidget<UTitleMenuWidget>(this, TitleMenuWidgetClass);
	if (IsValid(TitleMenuWidget))
	{
		TitleMenuWidget->AddToViewport(1);
	}
}