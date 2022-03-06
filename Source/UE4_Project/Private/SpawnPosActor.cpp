// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPosActor.h"

// Sets default values
ASpawnPosActor::ASpawnPosActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto Comp = CreateDefaultSubobject<USceneComponent>("POS COMP");
	RootComponent = Comp;
}
