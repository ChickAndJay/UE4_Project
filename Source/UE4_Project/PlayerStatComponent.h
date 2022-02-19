// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

		
public:	
	void SetHP(int NewHP);

	void AddDamage(int Damage);
	bool AddExp(int AdditionalExp);
	void AddLevel();

	int GetCurrentHP();
	void GetCurrentExp();
	int GetCurrentLevel();
	int GetCurrentStamina();
	int GetAttackDamage();
private:

	const int ADDITIONAL_HP_PER_LEVEL = 100;
	const int MAX_LEVEL = 5;	

	UPROPERTY(EditDefaultsOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int MaxHP;
	UPROPERTY(EditDefaultsOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int MaxExp;
	UPROPERTY(EditDefaultsOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int MaxStamina;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int CurrentHP;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int CurrentExp;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int CurrentLevel;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int CurrentStamina;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int AttackDamage;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int AdditionalStaminaPerSec;
};
