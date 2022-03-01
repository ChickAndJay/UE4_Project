// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnSceneComponent.h"
#include "MonsterActor.h"
#include "SpawnPosActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UMonsterSpawnSceneComponent::UMonsterSpawnSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Trigger Box
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX COMP"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &UMonsterSpawnSceneComponent::SpawnMonster);
	BoxComp->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));		
	BoxComp->SetRelativeLocation(FVector(0.f, 0.f, 130.f));

	// Particle
	MonsterSpawnParticleArr.Add(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE A")));
	MonsterSpawnParticleArr.Add(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE B")));
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PARTICLE_A(TEXT("/Game/CustomContent/Character/Monster/FX/MonsterSpawnFX_A.MonsterSpawnFX_A"));
	if (PARTICLE_A.Succeeded())
	{
		MonsterSpawnParticleArr[0]->SetTemplate(PARTICLE_A.Object);
		MonsterSpawnParticleArr[0]->bAutoActivate = false;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PARTICLE_B(TEXT("/Game/CustomContent/Character/Monster/FX/MonsterSpawnFX_B.MonsterSpawnFX_B"));
	if (PARTICLE_B.Succeeded())
	{
		MonsterSpawnParticleArr[1]->SetTemplate(PARTICLE_B.Object);
		MonsterSpawnParticleArr[1]->bAutoActivate = false;
	}
}

void UMonsterSpawnSceneComponent::SpawnMonster(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MYLOG_S();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetOwner()->GetWorld(), ASpawnPosActor::StaticClass(), OutActors);

	for (int idx = 0; idx < OutActors.Num(); idx++)
	{
		ASpawnPosActor* actor = Cast< ASpawnPosActor>(OutActors[idx]);
		if (actor != nullptr)
		{
			FRotator SpawnRotator = FRotator::ZeroRotator;
			SpawnRotator.Yaw = 180.0f;
			GetOwner()->GetWorld()->SpawnActor<AMonsterActor>(actor->GetActorLocation(), SpawnRotator);
			for (int spawnIdx = 0; spawnIdx < MonsterSpawnParticleArr.Num(); spawnIdx++)
			{
				MonsterSpawnParticleArr[spawnIdx]->SetWorldLocation(actor->GetActorLocation());
				MonsterSpawnParticleArr[spawnIdx]->Activate(true);
				MonsterSpawnParticleArr[spawnIdx]->OnSystemFinished.AddDynamic(this, &UMonsterSpawnSceneComponent::OnFinishSpawnEffect);
			}

			break;
		}
	}
}

void UMonsterSpawnSceneComponent::OnFinishSpawnEffect(UParticleSystemComponent* PSystem)
{
	PSystem->Activate(false);
}