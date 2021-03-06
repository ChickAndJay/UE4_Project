// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "GameFramework/Character.h"
#include "MonsterActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMonsterDeadDelegate);

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

protected:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UMonsterStatComponent* MonsterStatComp;
	UPROPERTY(VisibleAnywhere)
	class UMonsterAnimInstance* AnimInstance;
	UPROPERTY()
	class AMonsterAIController* AIController;
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(EditAnywhere, Category = MovingFactor)
	float MAX_JOG_VALUE = 600.0f;

	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackRange;
	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackRadius;

	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere)
	float DeadDestroyDelay = 3.0f;

	UPROPERTY(VisibleAnywhere)
	bool IsMoving;

	UPROPERTY(VisibleAnywhere)
	bool IsDead;

	ECharacterState MonsterState;

	FTimerHandle DeadTimerHandle = {};

public:	
	FOnMonsterDeadDelegate OnMonsterDead;

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
	float GetAttackRange();
	int GetDropExp();

	bool IsMonsterDead();	
	bool IsMonsterMoving();

	UFUNCTION()
	void RotateTo(FVector ToLocation);
	UFUNCTION()
	void MoveTo(FVector ToLocation);

	UFUNCTION()
	void StartMoving();
	UFUNCTION()
	void StopMoving();
};