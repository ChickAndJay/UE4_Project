// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UMonsterAnimInstance::UMonsterAnimInstance()
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
				TEXT("/Game/ParagonBoris/Characters/Heroes/Boris/Animations/Primary_%s_Montage.Primary_%s_Montage"),
				*PostFixList[idx],
				*PostFixList[idx]);

		//MYLOG(TEXT("%s"), *AttackMontagePath);

		ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(*AttackMontagePath);
		if (ATTACK_MONTAGE.Succeeded())
		{
			AttackAnimMontageArray.Add(ATTACK_MONTAGE.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> LEVEL_START_MONTAGE(TEXT("/Game/ParagonBoris/Characters/Heroes/Boris/Animations/LevelStart_Montage.LevelStart_Montage"));
	if (LEVEL_START_MONTAGE.Succeeded())
	{
		LevelStartMontage = LEVEL_START_MONTAGE.Object;
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

	Montage_Play(LevelStartMontage);
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(OwnerActor))
	{
		// Calculate Speed
		Speed = OwnerActor->GetVelocity().Size();
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
	}

	if (IsValid(CharacterMovementComponent))
	{
		// Check IsAccelerating
		FVector Acceleration = CharacterMovementComponent->GetCurrentAcceleration();
		if (Acceleration.Size() > 0)
			IsAccelerating = true;
		else
			IsAccelerating = false;

		//MYLOG(TEXT("IsAccelerating : %s"), IsAccelerating ? TEXT("TRUE") : TEXT("FALSE"));
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
}

void UMonsterAnimInstance::SetDead()
{
	IsDead = true;
}
