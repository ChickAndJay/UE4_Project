// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAmbientSound.h"
#include "Components/AudioComponent.h"

AGameAmbientSound::AGameAmbientSound()
{
	auto AudioSoundComp = GetAudioComponent();

	static ConstructorHelpers::FObjectFinder<USoundBase> BGM_WAIT_BATTLE(TEXT("/Game/CustomContent/Sounds/GameWaitBattleSoundCue.GameWaitBattleSoundCue"));
	if (BGM_WAIT_BATTLE.Succeeded())
	{
		WaitBGMCue = BGM_WAIT_BATTLE.Object;
		AudioSoundComp->SetSound(WaitBGMCue);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> BGM_PLAY_BATTLE(TEXT("/Game/CustomContent/Sounds/GamePlayBattleSoundCue.GamePlayBattleSoundCue"));
	if (BGM_PLAY_BATTLE.Succeeded())
	{
		BattleBGMCue = BGM_PLAY_BATTLE.Object;
		AudioSoundComp->SetSound(WaitBGMCue);
	}
}

void AGameAmbientSound::BeginPlay()
{
	Super::BeginPlay();

	auto AudioSoundComp = GetAudioComponent();
	AudioSoundComp->Stop();
}

void AGameAmbientSound::PlayBGM(USoundBase* NewSound)
{
	auto AudioSoundComp = GetAudioComponent();
	if (AudioSoundComp->IsPlaying())
	{
		AudioSoundComp->Stop();
	}

	AudioSoundComp->SetSound(NewSound);
	AudioSoundComp->Play();
}

void AGameAmbientSound::PlayWaitBattleBGM()
{
	MYLOG_S();
	PlayBGM(WaitBGMCue);
}

void AGameAmbientSound::PlayPlayBattleBGM()
{
	MYLOG_S();
	PlayBGM(BattleBGMCue);
}

