// Fill out your copyright notice in the Description page of Project Settings.


#include "KwangGameInstance.h"
#include "Engine/DataTable.h"
#include "CharacterDataManager.h"
#include "SkillDataManager.h"
#include "SoundManager.h"

UKwangGameInstance::UKwangGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> STATIC_CHARACTER(TEXT("/Game/CustomContent/DB_Data/static_character.static_character"));
	if (STATIC_CHARACTER.Succeeded())
	{
		CharacterDataManager::GetInstance()->SetCharacterLevelTable(STATIC_CHARACTER.Object);
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> STATIC_SKILL(TEXT("/Game/CustomContent/DB_Data/static_skill.static_skill"));
	if (STATIC_SKILL.Succeeded())
	{
		SkillDataManager::GetInstance()->SetSkillTable(STATIC_SKILL.Object);
	}
}

void UKwangGameInstance::Init()
{
	Super::Init();
	MYLOG_S();
}

void UKwangGameInstance::SetSoundManager(ASoundManager* NewSoundManager)
{
	if (NewSoundManager == nullptr)
		return;
	SoundManager = NewSoundManager;
}

ASoundManager* UKwangGameInstance::GetSoundManager()
{
	return SoundManager;
}