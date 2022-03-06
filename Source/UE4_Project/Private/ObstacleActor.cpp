// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AObstacleActor::AObstacleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> OBSTACLE_MESH(TEXT("/Game/CustomContent/Objects/Obstacle.Obstacle"));
	if (OBSTACLE_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(OBSTACLE_MESH.Object);
	}

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX COMP"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	BoxComp->SetCollisionProfileName(TEXT("BlockAll"));
	BoxComp->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	IsStartMoving = false;
	MoveSpeed = 20.0f;
}

// Called when the game starts or when spawned
void AObstacleActor::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalPos = GetActorLocation();
}

// Called every frame
void AObstacleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsStartMoving)
		return;

	FVector Location = GetActorLocation();

	Location -= GetActorUpVector() * MoveSpeed * DeltaTime;
	SetActorLocation(Location);

	float dist = FVector::Dist(OriginalPos, GetActorLocation());
	if (dist >= 200.0f)
	{
		Destroy();
	}
}

void AObstacleActor::MoveAway()
{
	IsStartMoving = true;
	MYLOG_S();
}

