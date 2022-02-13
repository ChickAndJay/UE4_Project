// Fill out your copyright notice in the Description page of Project Settings.


#include "KwangAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UKwangAnimInstance::NativeBeginPlay()
{
	IsAccelerating = false;
	RotationLastTick = FRotator::ZeroRotator;

	APlayerCharacter* Owner = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (IsValid(Owner))
	{
		OwnerPlayerCharacter = Owner;
		CharacterMovementComponent = Owner->GetCharacterMovement();
	}
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