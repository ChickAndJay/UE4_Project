// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MonsterSpawnSceneComponent.generated.h"

UENUM()
enum class MONSTER_CATEGORY : uint8
{
	Boris,
	Grux
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_PROJECT_API UMonsterSpawnSceneComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	const int MONSTER_CATEGORY_COUNT = 2;
	bool isOnceSpawned = false;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	class ASpawnPosActor* SpawnPos;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	class AObstacleActor* Obstacle;

	UPROPERTY(VisibleAnywhere)
	TArray<class UParticleSystemComponent*> MonsterSpawnParticleArr;

	UPROPERTY(VisibleAnywhere)
	class AGameAmbientSound* GameAmbientSound;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	MONSTER_CATEGORY MonsterCategory;

	UPROPERTY(VisibleAnywhere)
	class AMonsterActor* SpawnedMonster;

	UPROPERTY()
	class USoundBase* SpawningSound;
public:	
	// Sets default values for this component's properties
	UMonsterSpawnSceneComponent();

	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnMonster(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFinishSpawnEffect(UParticleSystemComponent* PSystem);

	UFUNCTION()
	void OnSpawnedMonsterDead();
};
