// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KwangAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UKwangAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
private:
};
