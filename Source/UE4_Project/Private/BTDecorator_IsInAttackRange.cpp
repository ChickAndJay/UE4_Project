// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "MonsterActor.h"
#include "MonsterAIController.h"
#include "PlayerCharacter.h"
#include "BlackBoardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("IsInAttackRange");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = false;

	auto Owner = Cast<AMonsterActor>(OwnerComp.GetAIOwner()->GetPawn());
	if (Owner == nullptr)
		return false;

	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackBoardKeys::TargetKey));
	if (Target == nullptr)
		return false;

	bResult = (Owner->GetDistanceTo(Target) <= Owner->GetAttackRange());
	return bResult;
}
