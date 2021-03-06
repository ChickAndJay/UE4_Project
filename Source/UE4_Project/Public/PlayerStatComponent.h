// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_PROJECT_API UPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TWeakObjectPtr<class APlayerCharacter> OwnerPlayerCharacter;

	const int MAX_LEVEL = 5;
	const int MAX_EXP = 50;
	const int SKILL_COUNT = 2;

	UPROPERTY(EditDefaultsOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float STAMINA_PER_ATTACK = 20;
	UPROPERTY(EditDefaultsOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float STAMINA_PER_JUMP = 20;
	UPROPERTY(EditDefaultsOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float STAMINA_PER_SKILL = 30;

	UPROPERTY(EditDefaultsOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int MaxHP;
	UPROPERTY(EditDefaultsOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int MaxExp;
	UPROPERTY(EditDefaultsOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float MaxStamina;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int CurrentHP;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int CurrentExp;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int CurrentLevel;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentStamina;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int AttackDamage;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float AdditionalStaminaPerTick;
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float ReductionalStaminaPerSprinting;

	UPROPERTY()
	int SkillIdxArr[2];

	UPROPERTY(VisibleAnywhere)
	class USkillHolderComponent* SkillHolder[2];
		
public:	
	void InitCharacterStatData();

	void SetHP(int NewHP);

	void Heal(int HealValue);
	void AddDamage(int Damage);
	bool AddExp(int AdditionalExp);
	void AddLevel();
	void LevelUpSkill(ESkillType);

	int GetMaxHP();
	float GetMaxStamina();
	int GetMaxExp();
	int GetCurrentHP();
	int GetCurrentExp();
	int GetCurrentLevel();
	float GetCurrentStamina();

	float GetHPRatio();
	float GetStaminaRatio();
	float GetExpRatio();

	int GetAttackDamage();

	void UpdateStamina();
	void ReduceStaminaByAttack();
	void ReduceStaminaByJump();
	void ReduceStamina(int reduceValue);

	bool IsEnableAttack();
	bool IsEnableJump();
	
	bool IsMaxLevel();

	class USkillHolderComponent* GetSkillHolderComp(ESkillType skillType);

	void UseFirstSkill_Q();
	void UseSecondSkill_E();
};
