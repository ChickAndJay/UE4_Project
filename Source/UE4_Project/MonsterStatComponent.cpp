// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStatComponent.h"
#include "MonsterActor.h"

// Sets default values for this component's properties
UMonsterStatComponent::UMonsterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHP = 100;
	CurrentHP = MaxHP;
	AttackDamage = 3;
}


// Called when the game starts
void UMonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMonsterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMonsterStatComponent::AddDamage(int Damage)
{
	SetHP(FMath::Clamp<float>(CurrentHP - Damage, 0, MaxHP));
}

void UMonsterStatComponent::SetHP(int NewHP)
{
	CurrentHP = NewHP;

	OnHPChanged.Broadcast();
	MYLOG(TEXT("Monster CurrentHP : %d"), CurrentHP);
}

int UMonsterStatComponent::GetCurrentHP()
{
	return CurrentHP;
}

float UMonsterStatComponent::GetHPRatio()
{
	return (float)CurrentHP / MaxHP;
}

int UMonsterStatComponent::GetAttackDamage()
{
	return AttackDamage;
}

int UMonsterStatComponent::GetDropExp()
{
	return DROP_EXP;
}