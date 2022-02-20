// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterActor.h"
#include "Components/CapsuleComponent.h"
#include "MonsterStatComponent.h"
#include "MonsterAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "MonsterHPBarWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"


// Sets default values
AMonsterActor::AMonsterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MonsterStatComp = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("MONSTER STAT"));
	
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP BAR WIDGET"));
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetDrawSize(FVector2D(120.0f, 20.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::World);
	HPBarWidget->SetupAttachment(RootComponent);	
	HPBarWidget->SetHiddenInGame(false);

	static ConstructorHelpers::FClassFinder<UMonsterHPBarWidget> UI_HP_BAR(TEXT("/Game/CustomContent/UI/MonsterSimpleHpBar.MonsterSimpleHpBar_C"));
	if (UI_HP_BAR.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HP_BAR.Class);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObject(TEXT("/Game/ParagonBoris/Characters/Heroes/Boris/Meshes/Boris.Boris"));
	if (MeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshObject.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(8.0f, 0.0f, -114.0f), FRotator(0.0f, -90.0f, 0.0f));
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_ANIM(TEXT("/Game/CustomContent/Character/Monster/Animation/MonsterAnimBlueprint.MonsterAnimBlueprint_C"));
	if (BP_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(BP_ANIM.Class);	

	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	GetCapsuleComponent()->SetCapsuleRadius(65.0f);		

	
}

// Called when the game starts or when spawned
void AMonsterActor::BeginPlay()
{
	Super::BeginPlay();

	MonsterState = ECharacterState::ALIVE;
	UMonsterHPBarWidget* MonsterHPBar = Cast<UMonsterHPBarWidget>(HPBarWidget->GetUserWidgetObject());
	if (IsValid(MonsterHPBar))
	{
		MonsterHPBar->BindMonsterStat(MonsterStatComp);
	}

	AGameModeBase *GameMode = GetWorld()->GetAuthGameMode();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (GameMode && PlayerController)
		PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetCharacter());
}

// Called every frame
void AMonsterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter != nullptr)
	{
		FVector CameraLocation = PlayerCharacter->GetCameraLocation();
		HPBarWidget->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CameraLocation));
	}
}

void AMonsterActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MonsterAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
}

float AMonsterActor::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInsTigator, AActor* DamageCause)
{
	int Damage = (int)Super::TakeDamage(DamageAmount, DamageEvent, EventInsTigator, DamageCause);

	MonsterStatComp->AddDamage(Damage);

	if (MonsterStatComp->GetCurrentHP() <= 0)
	{
		MonsterState = ECharacterState::DEAD;
		KillMonster();
	}
	return Damage;
}

void AMonsterActor::KillMonster()
{
	MonsterAnimInstance->SetDead();
	SetActorEnableCollision(false);
	SetCanBeDamaged(false);
	MYLOG_S();

	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle,
		FTimerDelegate::CreateLambda(
			[this]()->void {
				Destroy();
				}),
			DeadDestroyDelay,
				false
		);
}