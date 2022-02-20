// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_API UPlayerStatusBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void UpdateStatusWidget(float NewStatusValue);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UProgressBar* StatusProgressBar;
};
