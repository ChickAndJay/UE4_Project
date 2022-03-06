// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "GameAmbientSound.h"

// Sets default values
ASoundManager::ASoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASoundManager::SetGameAmbientSound(AGameAmbientSound* Sound)
{
	if (Sound == nullptr)
		return;
	BGSound = Sound;
}

AGameAmbientSound* ASoundManager::GetGameAmbientSound()
{
	return BGSound;
}
