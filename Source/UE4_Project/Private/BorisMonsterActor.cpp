// Fill out your copyright notice in the Description page of Project Settings.


#include "BorisMonsterActor.h"

ABorisMonsterActor::ABorisMonsterActor()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObject(TEXT("/Game/ParagonBoris/Characters/Heroes/Boris/Meshes/Boris.Boris"));
	if (MeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshObject.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(8.0f, 0.0f, -114.0f), FRotator(0.0f, -90.0f, 0.0f));
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_ANIM(TEXT("/Game/CustomContent/Character/Monster/Animation/MonsterAnimBlueprint.MonsterAnimBlueprint_C"));
	if (BP_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(BP_ANIM.Class);
}