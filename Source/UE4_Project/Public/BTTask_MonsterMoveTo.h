// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "BlackBoardKeys.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MonsterMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UBTTask_MonsterMoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
protected:
	FVector MoveToLocation;
	FName TargetLocationKey;

	class APlayerCharacter* Target;
	class AMonsterActor* Owner;
public:
	UBTTask_MonsterMoveTo();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	//virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	//virtual EBTNodeResult::Type PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
