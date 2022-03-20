#pragma once

#include "Engine/DataTable.h"
#include "UE4_Project.h"
#include "SkillData.generated.h"

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	FSkillData() :SkillIdx(1000), Level(1), Value(1), CoolTime(1), LaunchType(0), DurationCount(0)
	{};
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SkillIdx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SkillCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TargetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LaunchType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DurationCount;
};