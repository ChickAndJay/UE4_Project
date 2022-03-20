#pragma once

#include "UE4_Project.h"
#include "SkillData.h"

class SkillDataManager
{
private:
	SkillDataManager();

	static SkillDataManager* Instance;

	class UDataTable* SkillTable;
public:
	static SkillDataManager* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new SkillDataManager();
		}

		return Instance;
	}

	void SetSkillTable(class UDataTable* newDataTable);

	int GetSkillCategory(int skillIdx);
	int GetSkillLevel(int skillIdx);
	int GetSkillValue(int skillIdx);
	int GetCoolTime(int skillIdx);
	int GetLaunchType(int skillIdx);
	int GetDurationCount(int skillIdx);

	bool IsExistSkill(int skillIdx);
};

