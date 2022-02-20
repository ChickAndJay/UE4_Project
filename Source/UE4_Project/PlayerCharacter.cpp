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
		
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObject(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC"));
	if (MeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshObject.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(8.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	static ConstructorHelpers::FClassFinder<UKwangAnimInstance> BP_ANIM(TEXT("/Game/CustomContent/Character/Kwang/Animation/Kwang_AnimBlueprint_Custom.Kwang_AnimBlueprint_Custom_C"));
	if (BP_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(BP_ANIM.Class);

	PlayerStatComp = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("PLAYER STAT"));
	

	InitializeValues();
}

void APlayerCharacter::InitializeValues()
{
	JumpMaxHoldTime = 0.15f;
	
	AttackRange = 150.0f;
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
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	PlayerInputComponent->BindAction("LeftShift", IE_Pressed, this, &APlayerCharacter::SetSprint);
	PlayerInputComponent->BindAction("LeftShift", IE_Released, this, &APlayerCharacter::UnsetSprint);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	KwangAnimInstance = Cast<UKwangAnimInstance>(GetMesh()->GetAnimInstance());
	if (IsValid(KwangAnimInstance))
	{
		KwangAnimInstance->GetOnSaveAttackDelegate().AddUObject(this, &APlayerCharacter::CheckNextAttack);
		KwangAnimInstance->GetOnResetComboDelegate().AddUObject(this, &APlayerCharacter::ResetCombo);
	}
}

void APlayerCharacter::SetInputEnable()
{
	IsInputEnable = true;
}

void APlayerCharacter::CheckNextAttack()
{
	if (IsPressedComboInput)
	{
		IsPressedComboInput = false;
		ComboCount++;
		if (ComboCount > MAX_COMBO_COUNT)
			ComboCount = 1;
		KwangAnimInstance->PlayAttack(ComboCount);
		AttackCheck();
	}
}

void APlayerCharacter::ResetCombo()
{		
	SetEndAttackState();
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
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(GetAttackDamage(), DamageEvent, GetController(), this);
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

	PlayerStatComp->AddDamage(Damage);

	if (PlayerStatComp->GetCurrentHP() <= 0)
	{
		CharacterState = ECharacterState::DEAD;
		KillPlayer();
	}
	return Damage;
}

void APlayerCharacter::KillPlayer()
{

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

	if(IsSprinting && !IsForwardRunning)
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

	if (!IsAttacking)
	{		
		SetStartAttackState();

		KwangAnimInstance->PlayAttack(ComboCount);
		AttackCheck();
	}
	else
	{
		IsPressedComboInput = true;
	}
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
	IsSprinting = true;
}

void APlayerCharacter::UnsetSprint()
{
	IsSprinting = false;
}
// [end] Input Delegate