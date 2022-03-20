#pragma once

#include "UE4_Project.h"

class CharacterDataManager
{
private:
	CharacterDataManager();

	static CharacterDataManager* Instance;

	class UDataTable* CharacterLevelTable;
public:
	static CharacterDataManager* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new CharacterDataManager();
		}
			
		return Instance;
	}

	void SetCharacterLevelTable(class UDataTable* newDataTable);

	int GetCharacterMaxHP(int Level);
	int GetCharacterMaxStamina(int Level);

	int GetCharacterSkill1(int Level);
	int GetCharacterSkill2(int Level);
};

