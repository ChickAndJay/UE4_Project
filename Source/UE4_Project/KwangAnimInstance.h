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
	UKwangAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool isRunning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool isJumping;


	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
