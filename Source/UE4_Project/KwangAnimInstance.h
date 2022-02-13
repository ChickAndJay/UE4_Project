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

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	const float LEAN_INTENSITY_FACTOR = 7.0f;
	const float INTERP_SPEED = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Roll;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Pitch;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Yaw;

	UPROPERTY(BlueprintReadOnly)
	float YawDelta;
	UPROPERTY(BlueprintReadOnly)
	FRotator RotationLastTick;

	class UCharacterMovementComponent* CharacterMovementComponent;
	class APlayerCharacter* OwnerPlayerCharacter;
};
