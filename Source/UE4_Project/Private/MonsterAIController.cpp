// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BlackBoardKeys.h"

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

	// perception
	AIPerceptionComp = CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("MONSTER AI PERCEPTION"));
	if (AIPerceptionComp != nullptr)
	{
		SetPerceptionComponent(*AIPerceptionComp);
		AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnTargetDetected);
	}

	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("PERCEPTION SIGHT CONFIG"));
	if (SightConfig != nullptr)
	{
		SightConfig->SightRadius = 1000.0f;
		SightConfig->LoseSightRadius = 1000.0f;
		SightConfig->PeripheralVisionAngleDegrees = 360.0f;
		SightConfig->SetMaxAge(0.0f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = -1.0f;

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
			
		if (AIPerceptionComp != nullptr)
		{
			AIPerceptionComp->SetDominantSense(*SightConfig->GetSenseImplementation());
			AIPerceptionComp->ConfigureSense(*SightConfig);
		}
	}	
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	RunAI();
}

void AMonsterAIController::OnTargetDetected(AActor* actor, FAIStimulus Stimulus)
{
	auto blackboard = GetBlackboardComponent();
	blackboard->SetValueAsObject(BlackBoardKeys::TargetKey, actor);
	blackboard->SetValueAsVector(BlackBoardKeys::TargetLocationKey, actor->GetActorLocation());
}

void AMonsterAIController::RunAI()
{
	if (UseBlackboard(MonsterBB, Blackboard))
	{
		//Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(MonsterBT))
		{
			MYLOG(TEXT("AIController couldn't run behavior tree!"));
		}

		auto blackboard = GetBlackboardComponent();
		blackboard->SetValueAsBool(BlackBoardKeys::IsEnableRunningAIKey, false);
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

void AMonsterAIController::EnableAIRunning()
{
	auto blackboard = GetBlackboardComponent();
	blackboard->SetValueAsBool(BlackBoardKeys::IsEnableRunningAIKey, true);
}

void AMonsterAIController::DisableAIRunning()
{
	auto blackboard = GetBlackboardComponent();
	blackboard->SetValueAsBool(BlackBoardKeys::IsEnableRunningAIKey, false);
}
