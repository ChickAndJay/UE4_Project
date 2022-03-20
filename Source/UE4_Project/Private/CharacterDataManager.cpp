#include "CharacterDataManager.h"
#include "Engine/DataTable.h"
#include "CharacterLevelData.h"

CharacterDataManager* CharacterDataManager::Instance = nullptr;

CharacterDataManager::CharacterDataManager()
{

}

void CharacterDataManager::SetCharacterLevelTable(UDataTable* newDataTable)
{
	if (newDataTable == nullptr)
		return;
	CharacterLevelTable = newDataTable;
}

int CharacterDataManager::GetCharacterMaxHP(int Level)
{
	FCharacterLevelData* RowData = CharacterLevelTable->FindRow<FCharacterLevelData>(*FString::FromInt(Level), TEXT(""));
	return RowData->MAX_HP;
}

int CharacterDataManager::GetCharacterMaxStamina(int Level)
{
	FCharacterLevelData* RowData = CharacterLevelTable->FindRow<FCharacterLevelData>(*FString::FromInt(Level), TEXT(""));
	return RowData->MAX_STAMINA;
}

int CharacterDataManager::GetCharacterSkill1(int Level)
{
	FCharacterLevelData* RowData = CharacterLevelTable->FindRow<FCharacterLevelData>(*FString::FromInt(Level), TEXT(""));
	return RowData->SKILL_IDX_1_INIT;
}

int CharacterDataManager::GetCharacterSkill2(int Level)
{
	FCharacterLevelData* RowData = CharacterLevelTable->FindRow<FCharacterLevelData>(*FString::FromInt(Level), TEXT(""));
	return RowData->SKILL_IDX_2_INIT;
}