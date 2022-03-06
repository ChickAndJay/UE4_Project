// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"

UCLASS()
class UE4_PROJECT_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY()
	class AGameAmbientSound* BGSound;
public:	

	void SetGameAmbientSound(class AGameAmbientSound* Sound);
	class AGameAmbientSound* GetGameAmbientSound();
};
