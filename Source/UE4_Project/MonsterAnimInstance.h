// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KwangAnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance();

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	class UCharacterMovementComponent* CharacterMovementComponent;
	class AMonsterActor* OwnerActor;

	// [begin] Move
	const float LEAN_INTENSITY_FACTOR = 7.0f;
	const float INTERP_SPEED = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool IsAccelerating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float Roll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float Pitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float Yaw;

	UPROPERTY(BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float YawDelta;
	UPROPERTY(BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	FRotator RotationLastTick;
	// [end] Move

	UPROPERTY(VisibleAnywhere)
	TArray<UAnimMontage*> AttackAnimMontageArray;

	UPROPERTY(VisibleAnywhere)
	UAnimMontage* LevelStartMontage;


	// [begin] attack
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool IsDead;

public:
	FOnSaveAttackDelegate OnSaveAttack;
	FOnResetComboDelegate OnResetCombo;

	UFUNCTION()
	void Animnotify_EndLevelStartMontage();
	UFUNCTION()
	void Animnotify_SaveAttack();
	UFUNCTION()
	void Animnotify_ResetCombo();

	void PlayAttack(int combo);
	void SetDead();
	// [end] attack
};
