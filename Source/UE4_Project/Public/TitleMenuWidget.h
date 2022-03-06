// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Blueprint/UserWidget.h"
#include "TitleMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UTitleMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnClick_Start();
	UFUNCTION(BlueprintCallable)
	void OnClick_Option();
	UFUNCTION(BlueprintCallable)
	void OnClick_Exit();
private:
	UPROPERTY()
	class UButton* StartButton;
	UPROPERTY()
	class UButton* OptionButton;
	UPROPERTY()
	class UButton* ExitButton;
};
