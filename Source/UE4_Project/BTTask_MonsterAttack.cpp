// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterAttack.h"
#include "MonsterActor.h"
#include "MonsterAIController.h"

UBTTask_MonsterAttack::UBTTask_MonsterAttack()
{
	NodeName = TEXT("CUSTOM MONSTER ATTACK");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Monster = Cast<AMonsterActor>(OwnerComp.GetAIOwner()->GetPawn());
	if (Monster == nullptr)
		return EBTNodeResult::Failed;

	Monster->Attack();
	AttackDeltaTime = 0.f;

	return EBTNodeResult::InProgress;
}

void UBTTask_MonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AttackDeltaTime += DeltaSeconds;

	if(AttackDeltaTime >= ATTACK_DELAY)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
