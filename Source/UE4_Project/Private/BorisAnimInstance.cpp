// Fill out your copyright notice in the Description page of Project Settings.


#include "BorisAnimInstance.h"

UBorisAnimInstance::UBorisAnimInstance()
{
	MYLOG_S();
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BORIS_LEVEL_START_MONTAGE(TEXT("/Game/ParagonBoris/Characters/Heroes/Boris/Animations/LevelStart_Montage.LevelStart_Montage"));
	if (BORIS_LEVEL_START_MONTAGE.Succeeded())
	{
		LevelStartMontage = BORIS_LEVEL_START_MONTAGE.Object;
	}

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

		ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(*AttackMontagePath);
		if (ATTACK_MONTAGE.Succeeded())
		{
			AttackAnimMontageArray.Add(ATTACK_MONTAGE.Object);
		}
	}
}
