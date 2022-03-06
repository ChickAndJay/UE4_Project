// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(DM_UE4, Log, All);

#define MYLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define MYLOG_S() UE_LOG(DM_UE4, Warning, TEXT("%s"), *MYLOG_CALLINFO)
#define MYLOG(Format, ...) UE_LOG(DM_UE4, Warning, TEXT("%s %s"), *MYLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ALIVE,
	DEAD
};