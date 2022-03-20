// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KwangAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "PlayerStatComponent.h"
#include "KwangPlayerController.h"
#include "PlayerHUDWidget.h"
#include "MonsterActor.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameAmbientSound.h"
#include "KwangGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SoundManager.h"
#include "LevelUpUserWidget.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING ARM"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-10.0f, 0.0f, 0.0f));
    SpringArmComp->TargetArmLength = 400.f;
    SpringArmComp->bEnableCameraLag = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MAIN CAMERA"));
	Camera->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	AIPerceptionSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AI PERCEPTION SOURCE"));
	AIPerceptionSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());

	LevelUpParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LEVEL UP PARTICLE SYSTEM"));
	LevelUpParticleComp->SetupAttachment(RootComponent);

	HealParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HEAL PARTICLE SYSTEM"));
	HealParticleComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> LEVEL_UP_PARTICLE(TEXT("/Game/CustomContent/Character/Kwang/FX/LevelUp_FX.LevelUp_FX"));
	if (LEVEL_UP_PARTICLE.Succeeded())
	{
		LevelUpParticleComp->SetTemplate(LEVEL_UP_PARTICLE.Object);
		LevelUpParticleComp->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HEAL_PARTICLE(TEXT("/Game/CustomContent/Character/Kwang/FX/Heal_FX.Heal_FX"));
	if (HEAL_PARTICLE.Succeeded())
	{
		HealParticleComp->SetTemplate(HEAL_PARTICLE.Object);
		HealParticleComp->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObject(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC"));
	if (MeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshObject.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(8.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	static ConstructorHelpers::FClassFinder<UKwangAnimInstance> BP_ANIM(TEXT("/Game/CustomContent/Character/Kwang/Animation/Kwang_AnimBlueprint_Custom.Kwang_AnimBlueprint_Custom_C"));
	if (BP_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(BP_ANIM.Class);

	static ConstructorHelpers::FClassFinder<ULevelUpUserWidget> UI_LEVEL_UP_C(TEXT("/Game/CustomContent/UI/BP_LevelUpWidget.BP_LevelUpWidget_C"));
	if (UI_LEVEL_UP_C.Succeeded())
	{
		MYLOG(TEXT("LevelUp Class Find"));
		LevelUpWidgetClass = UI_LEVEL_UP_C.Class;
	}
	else
	{
		MYLOG(TEXT("LevelUp Class Find Failed"));
	}

	PlayerStatComp = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("PLAYER STAT"));
	

	InitializeValues();
}

void APlayerCharacter::InitializeValues()
{
	JumpMaxHoldTime = 0.15f;
	
	AttackRange = 200.0f;
	AttackRadius = 50.0f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ComboCount = 0;

	IsInputEnable = false;
	bPressedJump = false;

	IsAttacking = false;
	IsPressedComboInput = false;

	IsSprinting = false;
	IsForwardRunning = true;

	CharacterState = ECharacterState::ALIVE;

	KwangPlayerController = Cast<AKwangPlayerController>(GetController());
	PlayerHUDWidget = KwangPlayerController->GetPlayerHUDWidget();
	PlayerHUDWidget->BindPlayerStat(PlayerStatComp);
	PlayerHUDWidget->UpdatePlayerStatus();

	InstantiateSounds();
}

void APlayerCharacter::InstantiateSounds()
{
	auto instance = Cast<UKwangGameInstance>(UGameplayStatics::GetGameInstance(GetOwner()->GetWorld()));

	auto SoundManager = Cast<ASoundManager>(GetOwner()->GetWorld()->SpawnActor(ASoundManager::StaticClass()));
	instance->SetSoundManager(SoundManager);

	auto GameAmbientSound = Cast<AGameAmbientSound>(GetOwner()->GetWorld()->SpawnActor(AGameAmbientSound::StaticClass()));
	if (GameAmbientSound == nullptr)
	{
		MYLOG(TEXT("FAIL to make GameAmbientSound"));
	}
	else
	{
		GameAmbientSound->PlayWaitBattleBGM();
		
		SoundManager->SetGameAmbientSound(GameAmbientSound);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CharacterState == ECharacterState::ALIVE)
	{
		if (PlayerStatComp->GetCurrentStamina() <= KINDA_SMALL_NUMBER)
		{
			IsSprinting = false;
		}

		PlayerHUDWidget->UpdatePlayerStaminaStatus();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MouseWheel", this, &APlayerCharacter::RotateMouseWheel);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	PlayerInputComponent->BindAction("MouseLeftClick", IE_Pressed, this, &APlayerCharacter::Attack);

	PlayerInputComponent->BindAction("Q", IE_Released, this, &APlayerCharacter::FirstSkill_Q);
	PlayerInputComponent->BindAction("E", IE_Released, this, &APlayerCharacter::SecondSkill_E);

	PlayerInputComponent->BindAction("LeftShift", IE_Pressed, this, &APlayerCharacter::SetSprint);
	PlayerInputComponent->BindAction("LeftShift", IE_Released, this, &APlayerCharacter::UnsetSprint);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	KwangAnimInstance = Cast<UKwangAnimInstance>(GetMesh()->GetAnimInstance());
	if (IsValid(KwangAnimInstance))
	{
		KwangAnimInstance->OnSaveAttack.AddUObject(this, &APlayerCharacter::CheckNextAttack);
		KwangAnimInstance->OnResetCombo.AddUObject(this, &APlayerCharacter::ResetCombo);
		KwangAnimInstance->OnHealEnd.AddUObject(this, &APlayerCharacter::SetInputEnable);
	}
}

void APlayerCharacter::SetInputEnable()
{
	IsInputEnable = true;
}

void APlayerCharacter::SetInputDisable()
{
	IsInputEnable = false;
}

void APlayerCharacter::PlayerAttack()
{
	PlayerStatComp->ReduceStaminaByAttack();
	PlayerHUDWidget->UpdatePlayerStaminaStatus();

	KwangAnimInstance->PlayAttack(ComboCount);
	AttackCheck();
}

void APlayerCharacter::CheckNextAttack()
{
	if (IsPressedComboInput)
	{
		IsPressedComboInput = false;
		ComboCount++;
		if (ComboCount > MAX_COMBO_COUNT)
			ComboCount = 1;
		PlayerAttack();
	}
}

void APlayerCharacter::ResetCombo()
{		
	SetEndAttackState();
}

void APlayerCharacter::Heal(int HealValue)
{	
	PlayerStatComp->Heal(HealValue);
	HealParticleComp->SetWorldLocation(GetActorLocation());
	HealParticleComp->Activate(true);
	KwangAnimInstance->PlayHeal();

	PlayerHUDWidget->UpdatePlayerHPStatus();
}

void APlayerCharacter::SetStartAttackState()
{
	IsPressedComboInput = false;
	IsAttacking = true;
	ComboCount = 1;
}

void APlayerCharacter::SetEndAttackState()
{
	IsPressedComboInput = false;
	IsAttacking = false;
	ComboCount = 0;
}

void APlayerCharacter::AttackCheck()
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

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(GetAttackDamage(), DamageEvent, GetController(), this);
		}
	}

	if (bResult && HitResult.Actor.IsValid())
	{
		auto MonsterActor = Cast<AMonsterActor>(HitResult.Actor);
		if (MonsterActor != nullptr)
		{
			FDamageEvent DamageEvent;
			MonsterActor->TakeDamage(GetAttackDamage(), DamageEvent, GetController(), this);
			if (MonsterActor->IsMonsterDead())
			{
				int DropExp = MonsterActor->GetDropExp();
				if (PlayerStatComp->AddExp(DropExp))
				{
					LevelUpParticleComp->SetWorldLocation(GetActorLocation());
					LevelUpParticleComp->Activate(true);

					KwangAnimInstance->PlayLevelUpSound();

					GetWorld()->GetTimerManager().SetTimer(LevelUpTimerHandle,
						FTimerDelegate::CreateLambda(
							[this]()->void {
								auto LevelUpWidget = CreateWidget<ULevelUpUserWidget>(Cast<AKwangPlayerController>(GetController()), LevelUpWidgetClass);
								LevelUpWidget->BindPlayerCharacter(this);
								LevelUpWidget->AddToViewport(3);

								Cast<AKwangPlayerController>(GetController())->ChangeInputMode(false);

								LevelUpWidget->OnSkillLevelUp.AddLambda([this](ESkillType skillType)-> void {
									PlayerStatComp->LevelUpSkill(skillType);

									Cast<AKwangPlayerController>(GetController())->ChangeInputMode(true);

									PlayerHUDWidget->UpdatePlayerStatus();
									});
							}),
							1.0f,
							false);
				}
				else
					PlayerHUDWidget->UpdatePlayerExpStatus();
			}
			KwangAnimInstance->PlayHitSoundRandom();
		}
	}
}

int APlayerCharacter::GetAttackDamage()
{
	return PlayerStatComp->GetAttackDamage();
}

FVector APlayerCharacter::GetCameraLocation()
{
	return Camera->GetComponentLocation();
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInsTigator, AActor* DamageCause)
{
	int Damage = (int)Super::TakeDamage(DamageAmount, DamageEvent, EventInsTigator, DamageCause);

	MYLOG(TEXT("%d"), Damage);

	PlayerStatComp->AddDamage(Damage);

	if (PlayerStatComp->GetCurrentHP() <= 0)
	{
		CharacterState = ECharacterState::DEAD;
		KillPlayer();
	}

	PlayerHUDWidget->UpdatePlayerHPStatus();

	return Damage;
}

void APlayerCharacter::KillPlayer()
{
	KwangAnimInstance->SetDead();
	SetActorEnableCollision(false);
	SetCanBeDamaged(false);
}

//////////////////////// [begin] Input Delegate
void APlayerCharacter::MoveForward(float Value)
{
	if (!IsInputEnable)
		return;
	
	if (Value >= 0.f)
		IsForwardRunning = true;
	else
		IsForwardRunning = false;

	if(IsSprinting && IsForwardRunning)
		GetCharacterMovement()->MaxWalkSpeed = MAX_SPRINT_FACTOR;
	else
		GetCharacterMovement()->MaxWalkSpeed = MAX_JOG_VALUE;

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	if (!IsInputEnable)
		return;

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::StartJump()
{
	if (!IsInputEnable)
		return;
	if (!PlayerStatComp->IsEnableJump())
		return;
	if (GetCharacterMovement()->IsFalling())
		return;

	PlayerStatComp->ReduceStaminaByJump();
	PlayerHUDWidget->UpdatePlayerStaminaStatus();

	bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
	if (!IsInputEnable)
		return;
	bPressedJump = false;
}

void APlayerCharacter::Attack()
{
	if (!IsInputEnable)
		return;
	if (!IsValid(KwangAnimInstance))
		return;
	if (!PlayerStatComp->IsEnableAttack())
		return;

	if (!IsAttacking)
	{		
		SetStartAttackState();

		PlayerAttack();
	}
	else
	{
		IsPressedComboInput = true;
	}
}

void APlayerCharacter::FirstSkill_Q()
{
	MYLOG_S();
	PlayerStatComp->UseFirstSkill_Q();
}

void APlayerCharacter::SecondSkill_E()
{
	PlayerStatComp->UseSecondSkill_E();
}

void APlayerCharacter::AddControllerPitchInput(float Val)
{
	if (!IsInputEnable)
		return;

	if (!IsValid(SpringArmComp))
		return;

	FRotator NewRotation = SpringArmComp->GetComponentRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + -Val, ROT_LOOK_UP_MIN, ROT_LOOK_UP_MAX);
	SpringArmComp->SetWorldRotation(NewRotation);
}

void APlayerCharacter::AddControllerYawInput(float Val)
{
	if (!IsInputEnable)
		return;
	Super::AddControllerYawInput(Val);
}

void APlayerCharacter::RotateMouseWheel(float Val)
{
	if (!IsInputEnable)
		return;
	if (!IsValid(SpringArmComp))
		return;

	//UE_LOG(LogTemp, Warning, TEXT("RotateMouseWheel : %f"), Val);
	float newArmLength = FMath::Clamp(SpringArmComp->TargetArmLength + Val * ZOOM_FACTOR * (-1), ZOOM_MIN, ZOOM_MAX);
	SpringArmComp->TargetArmLength = newArmLength;
}

void APlayerCharacter::SetSprint()
{
	if (!IsInputEnable)
		return;

	IsSprinting = true;
}

void APlayerCharacter::UnsetSprint()
{
	if (!IsInputEnable)
		return;
	
	IsSprinting = false;
}
// [end] Input Delegate