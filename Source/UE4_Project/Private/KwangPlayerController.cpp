// Fill out your copyright notice in the Description page of Project Settings.


#include "KwangPlayerController.h"
#include "PlayerHUDWidget.h"

AKwangPlayerController::AKwangPlayerController()
{
	static ConstructorHelpers::FClassFinder<UPlayerHUDWidget> PLAYER_HUD_C(TEXT("/Game/CustomContent/UI/PlayerHUD.PlayerHUD_C"));
	if (PLAYER_HUD_C.Succeeded())
		PlayerHUDWidgetClass = PLAYER_HUD_C.Class;
}

void AKwangPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerHUDWidget = CreateWidget<UPlayerHUDWidget>(this, PlayerHUDWidgetClass);
	if (IsValid(PlayerHUDWidget))
	{
		PlayerHUDWidget->AddToViewport(1);
	}
}

UPlayerHUDWidget* AKwangPlayerController::GetPlayerHUDWidget()
{
	return PlayerHUDWidget;
}
