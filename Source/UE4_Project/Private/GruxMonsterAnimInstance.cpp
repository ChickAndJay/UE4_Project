// Fill out your copyright notice in the Description page of Project Settings.


#include "GruxMonsterAnimInstance.h"

UGruxMonsterAnimInstance::UGruxMonsterAnimInstance()
{
	MYLOG_S();
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GRUX_LEVEL_START_MONTAGE(TEXT("/Game/ParagonGrux/Characters/Heroes/Grux/Animations/LevelStart_Montage.LevelStart_Montage"));
	if (GRUX_LEVEL_START_MONTAGE.Succeeded())
	{
		LevelStartMontage = GRUX_LEVEL_START_MONTAGE.Object;
	}
	else
		MYLOG(TEXT("Not Exist Grux Montage"));

	TArray<FString> PostFixList;
	PostFixList.Add("A");
	PostFixList.Add("B");
	PostFixList.Add("C");
	PostFixList.Add("D");

	for (int idx = 0; idx < PostFixList.Num(); idx++)
	{
		FString AttackMontagePath =
			FString::Printf(
				TEXT("/Game/ParagonGrux/Characters/Heroes/Grux/Animations/Primary_%s_Montage.Primary_%s_Montage"),
				*PostFixList[idx],
				*PostFixList[idx]);

		ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(*AttackMontagePath);
		if (ATTACK_MONTAGE.Succeeded())
		{
			AttackAnimMontageArray.Add(ATTACK_MONTAGE.Object);
		}
	}
}