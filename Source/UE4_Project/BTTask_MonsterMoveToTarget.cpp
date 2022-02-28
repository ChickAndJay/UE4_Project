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

	ArriveCheckTolerance = 3.0f;
}

EBTNodeResult::Type UBTTask_MonsterMoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetLocationKey));
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	auto Owner = Cast<AMonsterActor>(OwnerComp.GetAIOwner()->GetPawn());
	ArriveCheckTolerance = Owner->GetAttackRange();

	MoveToLocation = Target->GetActorLocation();

	return EBTNodeResult::InProgress;
}