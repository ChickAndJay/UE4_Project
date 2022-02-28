// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlackBoardKeys.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MonsterMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UBTTask_MonsterMoveTo : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	FVector MoveToLocation;
	FName TargetLocationKey;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	float ArriveCheckTolerance;
public:
	UBTTask_MonsterMoveTo();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
