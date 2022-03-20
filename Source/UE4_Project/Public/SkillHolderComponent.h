// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Components/ActorComponent.h"
#include "SkillHolderComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSkillHolderChangeDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_PROJECT_API USkillHolderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillHolderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnSkillHolderChangeDelegate OnSkillChange;

	UPROPERTY(VisibleAnywhere, Category = Skill)
	int SkillIdx;
	UPROPERTY(VisibleAnywhere, Category = Skill)
	int SkillLevel;
	UPROPERTY(VisibleAnywhere, Category = Skill)
	float SkillCoolTime;
	UPROPERTY(VisibleAnywhere, Category = Skill)
	float CurrentCoolTime;
	
	UPROPERTY(VisibleAnywhere, Category = Skill)
	bool isAvailableCoolTime;
	UPROPERTY(VisibleAnywhere, Category = Skill)
	bool isAvailableSkillLevel;

	void SetSkillInfo(int NewSkillIdx);
	void UseSkill();
	void LevelUpSkill();

	int GetSkillCategory();
	float GetCurrentCoolTime();

	FORCEINLINE bool IsAvailableCoolTime()
	{
		return isAvailableCoolTime;
	}

	FORCEINLINE bool IsAvailableSkillLevel()
	{
		return isAvailableSkillLevel;
	}
};
