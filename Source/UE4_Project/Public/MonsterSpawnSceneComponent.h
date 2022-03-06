// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MonsterSpawnSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_PROJECT_API UMonsterSpawnSceneComponent : public USceneComponent
{
	GENERATED_BODY()

private:
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

	UPROPERTY(VisibleAnywhere)
	class AMonsterActor* SpawnedMonster;

	UPROPERTY()
	class USoundBase* SpawningSound;
public:	
	// Sets default values for this component's properties
	UMonsterSpawnSceneComponent();

	UFUNCTION()
	void SpawnMonster(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFinishSpawnEffect(UParticleSystemComponent* PSystem);

	UFUNCTION()
	void OnSpawnedMonsterDead();
};
