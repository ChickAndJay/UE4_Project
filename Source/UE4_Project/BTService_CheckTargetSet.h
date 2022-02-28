// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckTargetSet.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UBTService_CheckTargetSet : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CheckTargetSet();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
