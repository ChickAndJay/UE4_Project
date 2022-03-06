#pragma once

#include "Engine/DataTable.h"
#include "UE4_Project.h"
#include "CharacterLevelData.generated.h"

USTRUCT(BlueprintType)
struct FCharacterLevelData : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

		FCharacterLevelData() :LEVEL(1), MAX_HP(100), MAX_STAMINA(100)
	{};

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LEVEL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MAX_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MAX_STAMINA;
};