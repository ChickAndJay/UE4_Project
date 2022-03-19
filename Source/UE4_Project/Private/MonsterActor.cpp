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
#include "MonsterAIController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMonsterActor::AMonsterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MonsterStatComp = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("MONSTER STAT"));

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP BAR WIDGET"));
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HPBarWidget->SetDrawSize(FVector2D(120.0f, 10.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidget->SetupAttachment(RootComponent);	
	HPBarWidget->SetHiddenInGame(false);

	static ConstructorHelpers::FClassFinder<UMonsterHPBarWidget> UI_HP_BAR(TEXT("/Game/CustomContent/UI/MonsterHP.MonsterHP_C"));
	if (UI_HP_BAR.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HP_BAR.Class);
	}	

	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
	GetCapsuleComponent()->SetCapsuleRadius(65.0f);		

	GetCharacterMovement()->MaxWalkSpeed = MAX_JOG_VALUE;

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttackRange = 180.0f;
	AttackRadius = 50.0f;

	IsMoving = false;
	IsDead = false;
}

// Called when the game starts or when spawned
void AMonsterActor::BeginPlay()
{
	Super::BeginPlay();

	MonsterState = ECharacterState::ALIVE;

	AIController = Cast<AMonsterAIController>(GetController());

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
		FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CameraLocation);
		NewRotator.Pitch = 0;
		HPBarWidget->SetWorldRotation(NewRotator);
	}
}

void AMonsterActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
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

void AMonsterActor::Attack()
{
	PlayAttack();
}

void AMonsterActor::PlayAttack()
{
	AnimInstance->PlayAttack(1);
	AttackCheck();
}

void AMonsterActor::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

	if (bResult && HitResult.Actor.IsValid())
	{
		auto PlayerActor = Cast<APlayerCharacter>(HitResult.Actor);
		if (PlayerActor != nullptr)
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(GetAttackDamage(), DamageEvent, GetController(), this);

			AnimInstance->PlayHitSoundRandom();
		}
	}
}

void AMonsterActor::StartAIRunning()
{
	AIController->EnableAIRunning();
}

void AMonsterActor::KillMonster()
{
	IsDead = true;

	AnimInstance->SetDead();
	SetActorEnableCollision(false);
	SetCanBeDamaged(false);
	MYLOG_S();

	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle,
		FTimerDelegate::CreateLambda(
			[this]()->void {
				//AnimInstance->
				Destroy();
				}),
			DeadDestroyDelay,
				false
		);

	AIController->StopAI();
	OnMonsterDead.Broadcast();
	HPBarWidget->SetHiddenInGame(false);
}

int AMonsterActor::GetAttackDamage()
{
	return MonsterStatComp->GetAttackDamage();
}

float AMonsterActor::GetAttackRange()
{
	return AttackRange;
}

bool AMonsterActor::IsMonsterDead()
{
	return IsDead;
}

bool AMonsterActor::IsMonsterMoving()
{
	return IsMoving;
}

int AMonsterActor::GetDropExp()
{
	return MonsterStatComp->GetDropExp();
}

void AMonsterActor::RotateTo(FVector ToLocation)
{
	FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ToLocation);
	NewRotator.Pitch = 0;
	NewRotator.Roll = 0;
	SetActorRotation(NewRotator);
}

void AMonsterActor::MoveTo(FVector ToLocation)
{
	FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), ToLocation);
	AddMovementInput(Direction, 1.0f);

	RotateTo(ToLocation);
	StartMoving();
}

void AMonsterActor::StartMoving()
{
	IsMoving = true;
}

void AMonsterActor::StopMoving()
{
	IsMoving = false;
}
