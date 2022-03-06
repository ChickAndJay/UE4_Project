// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleMenuGameModeBase.h"
#include "TitleMenuPlayerController.h"

ATitleMenuGameModeBase::ATitleMenuGameModeBase()
{
	PlayerControllerClass = ATitleMenuPlayerController::StaticClass();
}