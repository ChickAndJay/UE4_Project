// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Sound/AmbientSound.h"
#include "GameAmbientSound.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API AGameAmbientSound : public AAmbientSound
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:
	AGameAmbientSound();

	UPROPERTY()
	USoundBase* WaitBGMCue;

	UPROPERTY()
	USoundBase* BattleBGMCue;

public:
	void PlayBGM(USoundBase* NewSound);
	void PlayWaitBattleBGM();
	void PlayPlayBattleBGM();
};
