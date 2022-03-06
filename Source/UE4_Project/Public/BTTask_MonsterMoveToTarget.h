// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterMoveTo.h"
#include "BTTask_MonsterMoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UBTTask_MonsterMoveToTarget : public UBTTask_MonsterMoveTo
{
	GENERATED_BODY()
	
public:
	UBTTask_MonsterMoveToTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
