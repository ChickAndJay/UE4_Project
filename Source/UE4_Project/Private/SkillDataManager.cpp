#include "SkillDataManager.h"
#include "Engine/DataTable.h"
#include "Containers/Map.h"

SkillDataManager* SkillDataManager::Instance = nullptr;

SkillDataManager::SkillDataManager()
{

}

void SkillDataManager::SetSkillTable(UDataTable* newDataTable)
{
	if (newDataTable == nullptr)
		return;
	SkillTable = newDataTable;
}

int SkillDataManager::GetSkillCategory(int skillIdx)
{
	FSkillData* RowData = SkillTable->FindRow<FSkillData>(*FString::FromInt(skillIdx), TEXT(""));
	if (RowData == nullptr)
		return 0;
	return RowData->SkillCategory;
}

int SkillDataManager::GetSkillLevel(int skillIdx)
{
	FSkillData* RowData = SkillTable->FindRow<FSkillData>(*FString::FromInt(skillIdx), TEXT(""));
	if (RowData == nullptr)
		return 0;
	return RowData->Level;
}

int SkillDataManager::GetSkillValue(int skillIdx)
{
	FSkillData* RowData = SkillTable->FindRow<FSkillData>(*FString::FromInt(skillIdx), TEXT(""));
	if (RowData == nullptr)
		return 0;
	return RowData->Value;
}

int SkillDataManager::GetCoolTime(int skillIdx)
{
	FSkillData* RowData = SkillTable->FindRow<FSkillData>(*FString::FromInt(skillIdx), TEXT(""));
	if (RowData == nullptr)
		return 0;
	return RowData->CoolTime;
}

int SkillDataManager::GetLaunchType(int skillIdx)
{
	FSkillData* RowData = SkillTable->FindRow<FSkillData>(*FString::FromInt(skillIdx), TEXT(""));
	if (RowData == nullptr)
		return 0;
	return RowData->LaunchType;
}

int SkillDataManager::GetDurationCount(int skillIdx)
{
	FSkillData* RowData = SkillTable->FindRow<FSkillData>(*FString::FromInt(skillIdx), TEXT(""));
	if (RowData == nullptr)
		return 0;
	return RowData->DurationCount;
}

bool SkillDataManager::IsExistSkill(int skillIdx)
{
	FSkillData* RowData = SkillTable->FindRow<FSkillData>(*FString::FromInt(skillIdx), TEXT(""));
	if (RowData == nullptr)
		return false;
	return true;
}