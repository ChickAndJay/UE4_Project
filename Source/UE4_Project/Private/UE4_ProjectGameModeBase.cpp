// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE4_ProjectGameModeBase.h"
#include "PlayerCharacter.h"
#include "KwangPlayerController.h"
#include "GameAmbientSound.h"
#include "Kismet/GameplayStatics.h"
#include "KwangGameInstance.h"

AUE4_ProjectGameModeBase::AUE4_ProjectGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AKwangPlayerController::StaticClass();
}
