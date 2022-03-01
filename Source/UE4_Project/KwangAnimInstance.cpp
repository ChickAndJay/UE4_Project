// Fill out your copyright notice in the Description page of Project Settings.


#include "KwangAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"

UKwangAnimInstance::UKwangAnimInstance()
{
	TArray<FString> PostFixList;
	PostFixList.Add("A");
	PostFixList.Add("B");
	PostFixList.Add("C");
	PostFixList.Add("D");

	for (int idx = 0; idx < PostFixList.Num(); idx++)
	{
		FString AttackMontagePath = 
			FString::Printf(
				TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_%s_Slow_Montage.PrimaryAttack_%s_Slow_Montage"), 
				*PostFixList[idx], 
				*PostFixList[idx]);
		
		//MYLOG(TEXT("%s"), *AttackMontagePath);

		ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(*AttackMontagePath);
		if (ATTACK_MONTAGE.Succeeded())
		{
			AttackAnimMontageArray.Add(ATTACK_MONTAGE.Object);
		}
	}

	for (int soundIdx = 0; soundIdx < 3; soundIdx++)
	{
		FString SoundPath =
			FString::Printf(
				TEXT("/Game/CustomContent/Character/Kwang/Sounds/AttackSounds/Kwang_Attack_%02d.Kwang_Attack_%02d"),
				soundIdx+1,
				soundIdx+1);
		
		ConstructorHelpers::FObjectFinder<USoundBase> ATTACK_SOUND_EFFECT(*SoundPath);
		if (ATTACK_SOUND_EFFECT.Succeeded())
		{
			AttackEffectSoundArr.Add(ATTACK_SOUND_EFFECT.Object);
		}
	}

	for (int soundIdx = 0; soundIdx < 8; soundIdx++)
	{
		FString SoundPath =
			FString::Printf(
				TEXT("/Game/CustomContent/Character/Kwang/Sounds/HitSounds/Metal_Hit_%d.Metal_Hit_%d"),
				soundIdx + 1,
				soundIdx + 1);

		ConstructorHelpers::FObjectFinder<USoundBase> HIT_SOUND_EFFECT(*SoundPath);
		if (HIT_SOUND_EFFECT.Succeeded())
		{
			HitEffectSoundArr.Add(HIT_SOUND_EFFECT.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> LEVEL_UP_SOUND_EFFECT(TEXT("/Game/CustomContent/Character/Kwang/Sounds/ActionSounds/Level_Up_Sound.Level_Up_Sound"));
	if (LEVEL_UP_SOUND_EFFECT.Succeeded())
	{
		LevelUpSound = LEVEL_UP_SOUND_EFFECT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> LEVEL_START_MONTAGE(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/LevelStart_Montage.LevelStart_Montage"));
	if (LEVEL_START_MONTAGE.Succeeded())
	{
		LevelStartMontage = LEVEL_START_MONTAGE.Object;
	}



	IsAccelerating = false;
	IsAttacking = false;
	IsDead = false;
	IsForward = true;

	RotationLastTick = FRotator::ZeroRotator;
}

void UKwangAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APlayerCharacter* Owner = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (IsValid(Owner))
	{
		OwnerActor = Owner;
		CharacterMovementComponent = Owner->GetCharacterMovement();
	}

	Montage_Play(LevelStartMontage);
}

void UKwangAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(OwnerActor))
	{
		// Calculate Speed
		Speed = OwnerActor->GetVelocity().Size();
		IsForward = OwnerActor->GetIsForwardRunning();
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

		IsSprinting = OwnerActor->GetIsSprinting();
	}

	if (IsValid(CharacterMovementComponent))
	{
		// Check IsAccelerating
		FVector Acceleration = CharacterMovementComponent->GetCurrentAcceleration();
		if (Acceleration.Size() > 0)
			IsAccelerating = true;
		else
			IsAccelerating = false;

		// Check IsInAir
		if (CharacterMovementComponent->IsFalling())
			IsInAir = true;
		else
			IsInAir = false;
	}
}

void UKwangAnimInstance::PlayAttack(int combo)
{
	IsAttacking = true;
	Montage_Play(AttackAnimMontageArray[combo - 1]);
	PlayAttackSoundRandom();
}

void UKwangAnimInstance::PlayAttackSoundRandom()
{
	int AttackSoundIdx = UKismetMathLibrary::RandomInteger(AttackEffectSoundArr.Num());	
	UGameplayStatics::PlaySoundAtLocation(OwnerActor->GetWorld(), AttackEffectSoundArr[AttackSoundIdx], OwnerActor->GetActorLocation());
}

void UKwangAnimInstance::PlayHitSoundRandom()
{
	int HitSoundIdx = UKismetMathLibrary::RandomInteger(HitEffectSoundArr.Num());
	UGameplayStatics::PlaySoundAtLocation(OwnerActor->GetWorld(), HitEffectSoundArr[HitSoundIdx], OwnerActor->GetActorLocation());
}

void UKwangAnimInstance::PlayLevelUpSound()
{
	UGameplayStatics::PlaySoundAtLocation(OwnerActor->GetWorld(), LevelUpSound, OwnerActor->GetActorLocation());
}

void UKwangAnimInstance::SetDead()
{
	IsDead = true;
}

void UKwangAnimInstance::Animnotify_EndLevelStartMontage()
{
	OwnerActor->SetInputEnable();
}

void UKwangAnimInstance::Animnotify_SaveAttack()
{
	OnSaveAttack.Broadcast();
}

void UKwangAnimInstance::Animnotify_ResetCombo()
{
	IsAttacking = false;
	OnResetCombo.Broadcast();
}