// Fill out your copyright notice in the Description page of Project Settings.


#include "KwangGameInstance.h"
#include "Engine/DataTable.h"
#include "CharacterDataManager.h"

UKwangGameInstance::UKwangGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> STATIC_CHARACTER(TEXT("/Game/CustomContent/DB_Data/static_character.static_character"));
	if (STATIC_CHARACTER.Succeeded())
	{
		CharacterDataManager::GetInstance()->SetCharacterLevelTable(STATIC_CHARACTER.Object);
	}
}

void UKwangGameInstance::Init()
{
	Super::Init();
	MYLOG_S();
}
