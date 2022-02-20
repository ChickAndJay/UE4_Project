// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UE4_PROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void InitializeValues();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;
private:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY()
	class UKwangAnimInstance* KwangAnimInstance;	
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UPlayerStatComponent* PlayerStatComp;

	UPROPERTY(EditAnywhere, Category = CameraFactor)
	float ZOOM_FACTOR = 10.0f;
	UPROPERTY(EditAnywhere, Category = CameraFactor)
	float ZOOM_MIN = 150.0f;
	UPROPERTY(EditAnywhere, Category = CameraFactor)
	float ZOOM_MAX = 800.0f;

	UPROPERTY(EditAnywhere, Category = CameraFactor)
	float ROT_LOOK_UP_MIN = -80.0f;
	UPROPERTY(EditAnywhere, Category = CameraFactor)
	float ROT_LOOK_UP_MAX = 30.0f;

	int MAX_COMBO_COUNT = 4;
	
	UPROPERTY(EditAnywhere, Category = MovingFactor)
	float MAX_JOG_VALUE = 600.0f;
	UPROPERTY(EditAnywhere, Category = MovingFactor)
	float MAX_SPRINT_FACTOR = 1000.0f;

	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackRange;
	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackRadius;
private:
	bool IsInputEnable;

	bool IsAttacking;
	bool IsPressedComboInput;
	int ComboCount;

	bool IsSprinting;
	bool IsForwardRunning;

	ECharacterState CharacterState;
public:
	void SetStartAttackState();
	void SetEndAttackState();

	void CheckNextAttack();
	void ResetCombo();

	FORCEINLINE bool GetIsSprinting()
	{
		return IsSprinting;
	}

	FORCEINLINE bool GetIsForwardRunning()
	{
		return IsForwardRunning;
	}

	int GetAttackDamage();
	FVector GetCameraLocation();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInsTigator, AActor* DamageCause) override;

	void KillPlayer();
public:
	UFUNCTION()
	void SetSprint();
	UFUNCTION()
	void UnsetSprint();

	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);
	
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void SetInputEnable();

	virtual void AddControllerPitchInput(float Val) override;
	virtual void AddControllerYawInput(float Val) override;

	void RotateMouseWheel(float Val);

	void AttackCheck();

};
