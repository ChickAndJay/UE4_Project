// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterMoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterAIController.h"
#include "MonsterActor.h"
#include "PlayerCharacter.h"

UBTTask_MonsterMoveToTarget::UBTTask_MonsterMoveToTarget()
{
	NodeName = TEXT("MonsterMoveToTarget");

	TargetKey = BlackBoardKeys::TargetKey;

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MonsterMoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey));
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	Owner = Cast<AMonsterActor>(OwnerComp.GetAIOwner()->GetPawn());
	if(Owner == nullptr)
		return EBTNodeResult::Failed;

	Owner->MoveTo(Target->GetActorLocation());
	Owner->RotateTo(Target->GetActorLocation());

	return EBTNodeResult::InProgress;
}

void UBTTask_MonsterMoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	bool isInAttackRange = (Owner->GetDistanceTo(Target) <= Owner->GetAttackRange());
	if (isInAttackRange)
	{
		Owner->StopMoving();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	Owner->MoveTo(Target->GetActorLocation());
}