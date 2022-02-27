// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIController();

private:
	UPROPERTY()
	class UBehaviorTree* MonsterBT;

	UPROPERTY()
	class UBlackboardData* MonsterBB;

public:
	void RunAI();
	void StopAI();
};
