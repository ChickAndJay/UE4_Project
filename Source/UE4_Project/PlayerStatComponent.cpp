// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatComponent.h"

// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHP = 100;
	MaxExp = 50;
	MaxStamina = 50;

	CurrentHP = MaxHP;
	CurrentExp = 0;
	CurrentLevel = 1;
	CurrentStamina = MaxStamina;

	AttackDamage = 10;

	AdditionalStaminaPerSec = 3;

	// ...
}


// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStatComponent::AddDamage(int Damage)
{
	CurrentHP -= Damage;

}

void UPlayerStatComponent::SetHP(int NewHP)
{

}

int UPlayerStatComponent::GetCurrentHP()
{
	return CurrentHP;
}

bool UPlayerStatComponent::AddExp(int AdditionalExp)
{
	CurrentExp += AdditionalExp;

	if (CurrentExp > MaxExp)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UPlayerStatComponent::GetCurrentExp()
{
}

void UPlayerStatComponent::AddLevel()
{
}

int UPlayerStatComponent::GetCurrentLevel()
{
	return 0;
}

int UPlayerStatComponent::GetCurrentStamina()
{
	return 0;
}

int UPlayerStatComponent::GetAttackDamage()
{
	return AttackDamage;
}