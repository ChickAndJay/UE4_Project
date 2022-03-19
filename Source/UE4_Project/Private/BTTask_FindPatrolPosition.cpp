// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPosition.h"
#include "MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "BlackBoardKeys.h"

UBTTask_FindPatrolPosition::UBTTask_FindPatrolPosition()
{
	NodeName = TEXT("FindPatrolPosition");
}

EBTNodeResult::Type UBTTask_FindPatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Owner = OwnerComp.GetAIOwner()->GetPawn();
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Owner->GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector From = Owner->GetActorLocation();
	FNavLocation To;	
	if (NavSystem->GetRandomReachablePointInRadius(From, 1000.0f, To))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackBoardKeys::PatrolLocationKey, To.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}