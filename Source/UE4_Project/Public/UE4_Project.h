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

UENUM(BlueprintType)
enum class ESkillCategory: uint8
{
	Heal,
	Poison
};

UENUM(BlueprintType)
enum class ESkillTargetType : uint8
{
	SELF,
	TARGET
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	FIRST,
	SECOND
};

UENUM(BlueprintType)
enum class ESkillUseType : uint8
{
	INSTANT,
	DOT
};