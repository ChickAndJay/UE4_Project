// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterAIController::AMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/CustomContent/AI/EnemyBB.EnemyBB"));
	if (BBObject.Succeeded())
	{
		MonsterBB = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/CustomContent/AI/EnemyBT.EnemyBT"));
	if (BTObject.Succeeded())
	{
		MonsterBT = BTObject.Object;
	}
}

void AMonsterAIController::RunAI()
{
	MYLOG_S();
	if (UseBlackboard(MonsterBB, Blackboard))
	{
		//Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(MonsterBT))
		{
			MYLOG(TEXT("AIController couldn't run behavior tree!"));
		}
	}
}

void AMonsterAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
