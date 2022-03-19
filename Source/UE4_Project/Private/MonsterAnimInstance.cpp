// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	for (int soundIdx = 0; soundIdx < 3; soundIdx++)
	{
		FString SoundPath =
			FString::Printf(
				TEXT("/Game/CustomContent/Character/Monster/Sounds/AttackSounds/Monster_Attack_Sound_%d.Monster_Attack_Sound_%d"),
				soundIdx + 1,
				soundIdx + 1);

		ConstructorHelpers::FObjectFinder<USoundBase> ATTACK_SOUND_EFFECT(*SoundPath);
		if (ATTACK_SOUND_EFFECT.Succeeded())
		{
			AttackEffectSoundArr.Add(ATTACK_SOUND_EFFECT.Object);
		}
	}

	for (int soundIdx = 0; soundIdx < 4; soundIdx++)
	{
		FString SoundPath =
			FString::Printf(
				TEXT("/Game/CustomContent/Character/Monster/Sounds/HitSounds/Monster_Hit_Medium_%d.Monster_Hit_Medium_%d"),
				soundIdx + 1,
				soundIdx + 1);

		ConstructorHelpers::FObjectFinder<USoundBase> HIT_SOUND_EFFECT(*SoundPath);
		if (HIT_SOUND_EFFECT.Succeeded())
		{
			HitEffectSoundArr.Add(HIT_SOUND_EFFECT.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> DYING_SOUND_EFFECT(TEXT("/Game/CustomContent/Character/Monster/Sounds/ActionSounds/Dying_Sound.Dying_Sound"));
	if (DYING_SOUND_EFFECT.Succeeded())
	{
		DyingSound = DYING_SOUND_EFFECT.Object;
	}

	IsInAir = false;
}

void UMonsterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	AMonsterActor* Owner = Cast<AMonsterActor>(TryGetPawnOwner());
	if (IsValid(Owner))
	{
		OwnerActor = Owner;
		CharacterMovementComponent = Owner->GetCharacterMovement();
	}

	MYLOG_S();
	if (LevelStartMontage == nullptr)
		MYLOG(TEXT("LevelStartMontage is nullptr"));
	Montage_Play(LevelStartMontage);
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(OwnerActor))
	{
		// Rool Pitch Yaw
		FRotator AimRotation = OwnerActor->GetBaseAimRotation();
		FRotator ActorRotation = OwnerActor->GetActorRotation();

		FRotator DeltaBetweenAimActor = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, ActorRotation);
		UKismetMathLibrary::BreakRotator(DeltaBetweenAimActor, Roll, Pitch, Yaw);

		// Yaw Delta for Leaning
		if (!RotationLastTick.IsZero())
		{
			FRotator DeltaLastRotation = UKismetMathLibrary::NormalizedDeltaRotator(RotationLastTick, ActorRotation);
			float PaddingValue;
			float TempDeltaYaw;
			UKismetMathLibrary::BreakRotator(DeltaLastRotation, PaddingValue, PaddingValue, TempDeltaYaw);
			float InterpTargetValue = (TempDeltaYaw / DeltaSeconds) / LEAN_INTENSITY_FACTOR;
			YawDelta = UKismetMathLibrary::FInterpTo(YawDelta, InterpTargetValue, DeltaSeconds, INTERP_SPEED);
		}

		RotationLastTick = ActorRotation;

		IsAccelerating = OwnerActor->IsMonsterMoving();
		if (IsAccelerating)
		{
			Speed = 100.0f;
		}
		else
		{
			Speed = 0.f;
		}
		//MYLOG(TEXT("MonsterAnim : %s %f"), IsAccelerating ? TEXT("TRUE") : TEXT("FALSE"), Speed);
	}
}

void UMonsterAnimInstance::Animnotify_EndLevelStartMontage()
{
	OwnerActor->StartAIRunning();
}

void UMonsterAnimInstance::Animnotify_SaveAttack()
{
	OnSaveAttack.Broadcast();
}

void UMonsterAnimInstance::Animnotify_ResetCombo()
{
	OnResetCombo.Broadcast();
}

void UMonsterAnimInstance::PlayAttack(int combo)
{
	IsAttacking = true;
	Montage_Play(AttackAnimMontageArray[combo - 1]);
	PlayAttackSoundRandom();
}

void UMonsterAnimInstance::PlayAttackSoundRandom()
{
	int AttackSoundIdx = UKismetMathLibrary::RandomInteger(AttackEffectSoundArr.Num());
	UGameplayStatics::PlaySoundAtLocation(OwnerActor->GetWorld(), AttackEffectSoundArr[AttackSoundIdx], OwnerActor->GetActorLocation());
}

void UMonsterAnimInstance::PlayHitSoundRandom()
{
	int HitSoundIdx = UKismetMathLibrary::RandomInteger(HitEffectSoundArr.Num());
	UGameplayStatics::PlaySoundAtLocation(OwnerActor->GetWorld(), HitEffectSoundArr[HitSoundIdx], OwnerActor->GetActorLocation());
}

void UMonsterAnimInstance::StopDeadSound()
{
	//UGameplayStatics::Stop
}

void UMonsterAnimInstance::SetDead()
{
	IsDead = true;
	UGameplayStatics::PlaySoundAtLocation(OwnerActor->GetWorld(), DyingSound, OwnerActor->GetActorLocation(), 1.0f, 1.0f, 11.5f);
}

