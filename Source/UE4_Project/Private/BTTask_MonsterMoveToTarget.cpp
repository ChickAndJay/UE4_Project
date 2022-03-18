// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterMoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterAIController.h"
#include "MonsterActor.h"
#include "PlayerCharacter.h"

UBTTask_MonsterMoveToTarget::UBTTask_MonsterMoveToTarget()
{
	NodeName = TEXT("MonsterMoveToTarget");

	TargetLocationKey = BlackBoardKeys::TargetKey;

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MonsterMoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetLocationKey));
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	Owner = Cast<AMonsterActor>(OwnerComp.GetAIOwner()->GetPawn());
	if(Owner == nullptr)
		return EBTNodeResult::Failed;
	ArriveCheckTolerance = Owner->GetAttackRange() - 50.0f;

	MoveToLocation = Target->GetActorLocation();

	return EBTNodeResult::InProgress;
}

void UBTTask_MonsterMoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	MoveToLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocationKey);

	ArriveCheckTolerance = Owner->GetAttackRange() - 50.0f;
	MoveToLocation = Target->GetActorLocation();

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
