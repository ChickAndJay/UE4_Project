// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckTargetSet.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterAIController.h"
#include "MonsterActor.h"
#include "BlackBoardKeys.h"

UBTService_CheckTargetSet::UBTService_CheckTargetSet()
{
	NodeName = TEXT("CheckTargetSet");
	Interval = 0.1f;
}

void UBTService_CheckTargetSet::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}