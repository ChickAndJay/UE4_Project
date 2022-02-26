// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Engine/GameInstance.h"
#include "KwangGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UKwangGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UKwangGameInstance();

	virtual void Init() override;
};
