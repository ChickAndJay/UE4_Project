// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterMoveTo.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterAIController.h"
#include "MonsterActor.h"

UBTTask_MonsterMoveTo::UBTTask_MonsterMoveTo()
{
	NodeName = TEXT("MonsterMoveTo");
	bNotifyTick = true;

	TargetLocationKey = BlackBoardKeys::PatrolLocationKey;
}

EBTNodeResult::Type UBTTask_MonsterMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	MoveToLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocationKey);
	Owner = Cast<AMonsterActor>(OwnerComp.GetAIOwner()->GetPawn());
	if (Owner != nullptr)
	{
		FVector OwnerLocation = Owner->GetActorLocation();
		FVector diff = MoveToLocation - OwnerLocation;

		Owner->RotateTo(MoveToLocation);
		Owner->StartMoving();
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_MonsterMoveTo::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
	
	Owner->StopMoving();
}