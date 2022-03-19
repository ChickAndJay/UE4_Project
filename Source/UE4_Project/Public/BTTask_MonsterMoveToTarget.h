// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlackBoardKeys.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MonsterMoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UBTTask_MonsterMoveToTarget : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	FVector MoveToLocation;
	FName TargetKey;
	FName TargetLocationKey;

	class APlayerCharacter* Target;
	class AMonsterActor* Owner;

	float ArriveCheckTolerance = 5.0f;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
public:
	UBTTask_MonsterMoveToTarget();
};
