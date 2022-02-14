// Fill out your copyright notice in the Description page of Project Settings.


#include "KwangAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> LEVEL_START_MONTAGE(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/LevelStart_Montage.LevelStart_Montage"));
	if (LEVEL_START_MONTAGE.Succeeded())
	{
		LevelStartMontage = LEVEL_START_MONTAGE.Object;
	}

	IsAccelerating = false;
	IsAttacking = false;
	RotationLastTick = FRotator::ZeroRotator;
}

void UKwangAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APlayerCharacter* Owner = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (IsValid(Owner))
	{
		OwnerPlayerCharacter = Owner;
		CharacterMovementComponent = Owner->GetCharacterMovement();
	}

	Montage_Play(LevelStartMontage);
}

void UKwangAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(OwnerPlayerCharacter))
	{
		// Calculate Speed
		Speed = OwnerPlayerCharacter->GetVelocity().Size();

		// Rool Pitch Yaw
		FRotator AimRotation = OwnerPlayerCharacter->GetBaseAimRotation();
		FRotator ActorRotation = OwnerPlayerCharacter->GetActorRotation();

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
}

void UKwangAnimInstance::Animnotify_EndLevelStartMontage()
{
	OwnerPlayerCharacter->SetInputEnable();
}

void UKwangAnimInstance::Animnotify_SaveAttack()
{
	OnSaveAttack.Broadcast();
}

void UKwangAnimInstance::Animnotify_ResetCombo()
{
	OnResetCombo.Broadcast();
}