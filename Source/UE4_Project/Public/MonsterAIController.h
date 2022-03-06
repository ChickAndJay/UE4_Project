// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
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

	virtual void BeginPlay() override;
private:
	UPROPERTY()
	class UBehaviorTree* MonsterBT;

	UPROPERTY()
	class UBlackboardData* MonsterBB;

	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY()
	class UAIPerceptionComponent* AIPerceptionComp;
public:
	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus Stimulus);

	void RunAI();
	void StopAI();

	void EnableAIRunning();
	void DisableAIRunning();
};
