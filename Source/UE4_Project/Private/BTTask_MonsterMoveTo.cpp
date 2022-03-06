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

	ArriveCheckTolerance = 5.0f;
}

EBTNodeResult::Type UBTTask_MonsterMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MoveToLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocationKey);

	return EBTNodeResult::InProgress;
}

void UBTTask_MonsterMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Owner = Cast<AMonsterActor>(OwnerComp.GetAIOwner()->GetPawn());
	if(Owner == nullptr)
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	FVector OwnerLocation = Owner->GetActorLocation();
	FVector diff = MoveToLocation - OwnerLocation;

	if (diff.IsNearlyZero(ArriveCheckTolerance))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	Owner->MoveTo(MoveToLocation);
}
