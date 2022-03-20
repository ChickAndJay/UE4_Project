// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatComponent.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterDataManager.h"
#include "SkillHolderComponent.h"

// Sets default values for this component's properties
UPlayerStatComponent::UPlayerStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHP = 100;
	MaxExp = MAX_EXP;
	MaxStamina = 50.0f;

	CurrentHP = MaxHP;
	CurrentExp = 0;
	CurrentLevel = 1;
	CurrentStamina = MaxStamina;

	AttackDamage = 10;

	AdditionalStaminaPerTick = 0.2f;
	ReductionalStaminaPerSprinting = 0.2f;

	int firstSkillIdx = static_cast<int>(ESkillType::FIRST);
	int secondSkillIdx = static_cast<int>(ESkillType::SECOND);

	SkillHolder[firstSkillIdx] = CreateDefaultSubobject<USkillHolderComponent>(TEXT("Skill First"));
	SkillHolder[secondSkillIdx] = CreateDefaultSubobject<USkillHolderComponent>(TEXT("Skill Second"));
	// ...
}


// Called when the game starts
void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	InitCharacterStatData();

	OwnerPlayerCharacter = Cast<APlayerCharacter>(GetOwner());
}


// Called every frame
void UPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateStamina();
	// ...
}

void UPlayerStatComponent::InitCharacterStatData()
{
	MaxHP = CharacterDataManager::GetInstance()->GetCharacterMaxHP(CurrentLevel);
	MaxStamina = CharacterDataManager::GetInstance()->GetCharacterMaxStamina(CurrentLevel);
	
	CurrentHP = MaxHP;
	CurrentStamina = MaxStamina;

	CurrentExp = 0;

	int firstSkillIdx = static_cast<int>(ESkillType::FIRST);
	int secondSkillIdx = static_cast<int>(ESkillType::SECOND);

	SkillIdxArr[firstSkillIdx] = CharacterDataManager::GetInstance()->GetCharacterSkill1(CurrentLevel);
	SkillIdxArr[secondSkillIdx] = CharacterDataManager::GetInstance()->GetCharacterSkill2(CurrentLevel);

	MYLOG(TEXT("Skill Idx : %d %d"), SkillIdxArr[firstSkillIdx], SkillIdxArr[secondSkillIdx]);

	SkillHolder[firstSkillIdx]->SetSkillInfo(SkillIdxArr[firstSkillIdx]);
	SkillHolder[secondSkillIdx]->SetSkillInfo(SkillIdxArr[secondSkillIdx]);
}

void UPlayerStatComponent::Heal(int HealValue)
{
	SetHP(FMath::Clamp<float>(CurrentHP + HealValue, 0, MaxHP));
	ReduceStamina(STAMINA_PER_SKILL);
}

void UPlayerStatComponent::AddDamage(int Damage)
{
	SetHP(FMath::Clamp<float>(CurrentHP - Damage, 0, MaxHP));
}

void UPlayerStatComponent::SetHP(int NewHP)
{
	CurrentHP = NewHP;
}

int UPlayerStatComponent::GetCurrentHP()
{
	return CurrentHP;
}

bool UPlayerStatComponent::AddExp(int AdditionalExp)
{
	if (IsMaxLevel())
		return false;

	CurrentExp += AdditionalExp;
	if (CurrentExp >= MaxExp)
	{
		AddLevel();
		return true;
	}
	else
	{
		return false;
	}
}

int UPlayerStatComponent::GetCurrentExp()
{
	return CurrentExp;
}

void UPlayerStatComponent::AddLevel()
{
	if(CurrentLevel < MAX_LEVEL)
		CurrentLevel++;
	InitCharacterStatData();
}

void UPlayerStatComponent::LevelUpSkill(ESkillType LevelUpSkillType)
{
	int skillSlotIdx = static_cast<int>(LevelUpSkillType);
	SkillHolder[skillSlotIdx]->LevelUpSkill();
}

int UPlayerStatComponent::GetMaxHP()
{
	return MaxHP;
}

float UPlayerStatComponent::GetMaxStamina()
{
	return MaxStamina;
}

int UPlayerStatComponent::GetMaxExp()
{
	return MaxExp;
}

int UPlayerStatComponent::GetCurrentLevel()
{
	return CurrentLevel;
}

float UPlayerStatComponent::GetCurrentStamina()
{
	return CurrentStamina;
}

float UPlayerStatComponent::GetHPRatio()
{
	return (float)CurrentHP / MaxHP;
}

float UPlayerStatComponent::GetStaminaRatio()
{
	return CurrentStamina / MaxStamina;
}

float UPlayerStatComponent::GetExpRatio()
{
	return (float)CurrentExp / MaxExp;
}

int UPlayerStatComponent::GetAttackDamage()
{
	return AttackDamage;
}

void UPlayerStatComponent::UpdateStamina()
{
	if (OwnerPlayerCharacter.IsValid())
	{
		FVector Acceleration = OwnerPlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration();
		if (OwnerPlayerCharacter->GetIsSprinting() && Acceleration.Size() > 0)
		{
			CurrentStamina = FMath::Clamp<float>(CurrentStamina - ReductionalStaminaPerSprinting, 0, MaxStamina);
		}
		else
		{
			CurrentStamina = FMath::Clamp<float>(CurrentStamina + AdditionalStaminaPerTick, 0, MaxStamina);
		}
	}
	else
	{
		CurrentStamina = FMath::Clamp<float>(CurrentStamina + AdditionalStaminaPerTick, 0, MaxStamina);
	}
}

void UPlayerStatComponent::ReduceStaminaByAttack()
{
	ReduceStamina(STAMINA_PER_ATTACK);
}

void UPlayerStatComponent::ReduceStaminaByJump()
{
	ReduceStamina(STAMINA_PER_JUMP);
}

void UPlayerStatComponent::ReduceStamina(int reduceValue)
{
	CurrentStamina = FMath::Clamp<float>(CurrentStamina - reduceValue, 0, MaxStamina);
}

bool UPlayerStatComponent::IsEnableAttack()
{
	return CurrentStamina >= STAMINA_PER_ATTACK;
}

bool UPlayerStatComponent::IsEnableJump()
{
	return CurrentStamina >= STAMINA_PER_JUMP;
}

bool UPlayerStatComponent::IsMaxLevel()
{
	return CurrentLevel >= MAX_LEVEL;
}

USkillHolderComponent* UPlayerStatComponent::GetSkillHolderComp(ESkillType skillType)
{
	int skillIdx = static_cast<int>(skillType);
	return SkillHolder[skillIdx];
}

void UPlayerStatComponent::UseFirstSkill_Q()
{
	int skillIdx = static_cast<int>(ESkillType::FIRST);
	SkillHolder[skillIdx]->UseSkill();
}

void UPlayerStatComponent::UseSecondSkill_E()
{
	int skillIdx = static_cast<int>(ESkillType::SECOND);
	SkillHolder[skillIdx]->UseSkill();
}
