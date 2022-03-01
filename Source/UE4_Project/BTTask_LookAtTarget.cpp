// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LookAtTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterAIController.h"
#include "MonsterActor.h"
#include "PlayerCharacter.h"
#include "BlackBoardKeys.h"

UBTTask_LookAtTarget::UBTTask_LookAtTarget()
{
	NodeName = TEXT("LookAtTarget");
}

EBTNodeResult::Type UBTTask_LookAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackBoardKeys::TargetKey));
	if (Target == nullptr)
		return EBTNodeResult::Failed;

	auto Owner = Cast<AMonsterActor>(OwnerComp.GetAIOwner()->GetPawn());

	FVector LookVector = Target->GetActorLocation() - Owner->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Owner->SetActorRotation(FMath::RInterpTo(Owner->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));


	return EBTNodeResult::Succeeded;
}
