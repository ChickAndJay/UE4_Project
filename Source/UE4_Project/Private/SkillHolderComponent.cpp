// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillHolderComponent.h"
#include "SkillDataManager.h"
#include "PlayerCharacter.h"
// Sets default values for this component's properties
USkillHolderComponent::USkillHolderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SkillIdx = 0;
	SkillLevel = 0;
	SkillCoolTime = 0;
	CurrentCoolTime = 0;

	isAvailableCoolTime = false;
	isAvailableSkillLevel = false;
	// ...
}


// Called when the game starts
void USkillHolderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkillHolderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isAvailableSkillLevel && !isAvailableCoolTime)
	{
		CurrentCoolTime -= DeltaTime;
		if (CurrentCoolTime <= 0.f)
		{
			isAvailableCoolTime = true;
			CurrentCoolTime = 0.f;
		}

		OnSkillChange.Broadcast();
	}
	// ...
}

void USkillHolderComponent::SetSkillInfo(int NewSkillIdx)
{
	MYLOG(TEXT("NewSkillIdx : %d"), NewSkillIdx);
	if (!SkillDataManager::GetInstance()->IsExistSkill(NewSkillIdx))
		return;
	
	SkillIdx = NewSkillIdx;

	SkillLevel = SkillDataManager::GetInstance()->GetSkillLevel(SkillIdx);
	SkillCoolTime = SkillDataManager::GetInstance()->GetSkillLevel(SkillIdx);
	CurrentCoolTime = 0;

	if (SkillLevel > 0)
	{
		isAvailableSkillLevel = true;
		isAvailableCoolTime = true;
	}

	OnSkillChange.Broadcast();
}

void USkillHolderComponent::UseSkill()
{
	if (!(isAvailableSkillLevel && isAvailableCoolTime))
		return;

	if (SkillDataManager::GetInstance()->GetSkillCategory(SkillIdx) == static_cast<int>(ESkillCategory::Heal))
	{
		int healValue = SkillDataManager::GetInstance()->GetSkillValue(SkillIdx);
		MYLOG(TEXT("healValue : %d %d"), healValue, SkillIdx);
		auto Owner =  Cast<APlayerCharacter>(GetOwner());
		Owner->SetInputDisable();
		Owner->Heal(healValue);

		isAvailableCoolTime = false;
		CurrentCoolTime = SkillDataManager::GetInstance()->GetCoolTime(SkillIdx);
	}
	else if (SkillDataManager::GetInstance()->GetSkillCategory(SkillIdx) == static_cast<int>(ESkillCategory::Poison))
	{

	}
}

void USkillHolderComponent::LevelUpSkill()
{
	SetSkillInfo(SkillIdx + 1);
}

int USkillHolderComponent::GetSkillCategory()
{
	return SkillDataManager::GetInstance()->GetSkillCategory(SkillIdx);
}

float USkillHolderComponent::GetCurrentCoolTime()
{
	return CurrentCoolTime;
}