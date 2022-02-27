// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "GameFramework/Character.h"
#include "MonsterActor.generated.h"

UCLASS()
class UE4_PROJECT_API AMonsterActor : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInsTigator, AActor* DamageCause) override;

	UFUNCTION()
	void Attack();
	void PlayAttack();
	void AttackCheck();

	void StartAIRunning();

	void KillMonster();

	int GetAttackDamage();
private:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UMonsterStatComponent* MonsterStatComp;
	UPROPERTY()
	class UMonsterAnimInstance* AnimInstance;
	UPROPERTY()
	class AMonsterAIController* AIController;
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackRange;
	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackRadius;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere)
	float DeadDestroyDelay = 3.0f;

	ECharacterState MonsterState;

	FTimerHandle DeadTimerHandle = {};
};