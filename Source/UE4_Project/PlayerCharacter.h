// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	bool IsInputEnable = false;
	
	UPROPERTY(EditAnywhere)
	float ZOOM_FACTOR = 10.0f;
	UPROPERTY(EditAnywhere)
	float ZOOM_MIN = 150.0f;
	UPROPERTY(EditAnywhere)
	float ZOOM_MAX = 800.0f;

	UPROPERTY(EditAnywhere)
	float ROT_LOOK_UP_MIN = -80.0f;
	UPROPERTY(EditAnywhere)
	float ROT_LOOK_UP_MAX = 30.0f;
public:
	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);
	
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void SetInputEnable(UAnimMontage* Montage, bool bInterrupted)
	{
		IsInputEnable = true;
	}

	virtual void AddControllerPitchInput(float Val) override;
	virtual void AddControllerYawInput(float Val) override;

	void RotateMouseWheel(float Val);
};
