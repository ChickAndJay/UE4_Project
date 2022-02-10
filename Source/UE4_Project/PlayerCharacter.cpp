// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "KwangAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING ARM"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-10.0f, 0.0f, 0.0f));
    SpringArmComp->TargetArmLength = 400.f;
    SpringArmComp->bEnableCameraLag = false;
    //SpringArmComp->CameraLagSpeed = 3.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MAIN CAMERA"));
	Camera->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
		
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObject(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC"));
	if (MeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshObject.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(8.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	static ConstructorHelpers::FClassFinder<UKwangAnimInstance> BP_ANIM(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/Kwang_AnimBlueprint.Kwang_AnimBlueprint_C"));
	if (BP_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BP_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	isInputEnable = false;
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
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	KwangAnimInstance = Cast<UKwangAnimInstance>(GetMesh()->GetAnimInstance());
	KwangAnimInstance->OnMontageEnded.AddDynamic(this, &APlayerCharacter::SetInputEnable);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (!isInputEnable)
		return;
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	if (!isInputEnable)
		return;
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::AddControllerPitchInput(float Val)
{
	Super::AddControllerPitchInput(Val);

	SpringArmComp->AddRelativeRotation(FRotator(-Val, 0.0f, 0.0f));
}