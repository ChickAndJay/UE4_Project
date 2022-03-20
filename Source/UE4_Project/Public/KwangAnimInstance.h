// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Animation/AnimInstance.h"
#include "KwangAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSaveAttackDelegate);
DECLARE_MULTICAST_DELEGATE(FOnResetComboDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHealEndDelegate);
/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UKwangAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UKwangAnimInstance();

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY()
	class UCharacterMovementComponent* CharacterMovementComponent;	
	UPROPERTY()
	class APlayerCharacter* OwnerActor;
	UPROPERTY()
	TArray<class USoundBase*> AttackEffectSoundArr;
	UPROPERTY()
	TArray<class USoundBase*> HitEffectSoundArr;
	UPROPERTY()
	class USoundBase* LevelUpSound;
	UPROPERTY()
	class USoundBase* HealSound;

	// [begin] Move
	const float LEAN_INTENSITY_FACTOR = 7.0f;
	const float INTERP_SPEED = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool IsAccelerating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool IsSprinting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool IsForward;
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

	UPROPERTY(VisibleAnywhere)
	UAnimMontage* HealMontage;
	

	// [begin] attack
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool IsDead;

public:
	FOnSaveAttackDelegate OnSaveAttack;
	FOnResetComboDelegate OnResetCombo;
	FOnHealEndDelegate OnHealEnd;
public:

	UFUNCTION()
	void Animnotify_EndLevelStartMontage();
	UFUNCTION()
	void Animnotify_SaveAttack();
	UFUNCTION()
	void Animnotify_ResetCombo();
	UFUNCTION()
	void Animnotify_HealEnd();

	void PlayHeal();
	void PlayAttack(int combo);
	void PlayAttackSoundRandom();
	void PlayHitSoundRandom();
	void PlayLevelUpSound();
	void SetDead();
	// [end] attack
};
