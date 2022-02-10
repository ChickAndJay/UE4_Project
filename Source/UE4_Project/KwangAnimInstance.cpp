// Fill out your copyright notice in the Description page of Project Settings.


#include "KwangAnimInstance.h"
#include "PlayerCharacter.h"

UKwangAnimInstance::UKwangAnimInstance()
{

}

void UKwangAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Owner = TryGetPawnOwner();

	if (!::IsValid(Owner)) return;

	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(Owner);
	if (playerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("NativeUpdateAnimation : %s"), playerCharacter->IsRunning() ? TEXT("true") : TEXT("false"));
		isRunning = playerCharacter->IsRunning();
	}
}
