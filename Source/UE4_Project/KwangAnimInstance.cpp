// Fill out your copyright notice in the Description page of Project Settings.


#include "KwangAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UKwangAnimInstance::NativeBeginPlay()
{
	IsAccelerating = false;

	APlayerCharacter* Owner = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (IsValid(Owner))
	{
		CharacterMovement = Owner->GetCharacterMovement();
	}
}

void UKwangAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterMovement)
	{
		FVector Acceleration = CharacterMovement->GetCurrentAcceleration();
		if (Acceleration.Size() > 0)
			IsAccelerating = true;
		else
			IsAccelerating = false;
	}
}