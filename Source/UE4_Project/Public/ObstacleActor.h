// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4_Project.h"
#include "GameFramework/Actor.h"
#include "ObstacleActor.generated.h"

UCLASS()
class UE4_PROJECT_API AObstacleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	class UBoxComponent* BoxComp;

	struct FVector OriginalPos;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	float MoveSpeed;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	bool IsStartMoving = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveAway();
};
