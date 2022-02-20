// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "GameFramework/PlayerController.h"
#include "TitleMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API ATitleMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATitleMenuPlayerController();
	
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TSubclassOf<class UTitleMenuWidget> TitleMenuWidgetClass;
	UPROPERTY()
	class UTitleMenuWidget* TitleMenuWidget;
	
};
