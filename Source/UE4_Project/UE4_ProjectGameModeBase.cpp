// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE4_ProjectGameModeBase.h"
#include "PlayerCharacter.h"

AUE4_ProjectGameModeBase::AUE4_ProjectGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
}