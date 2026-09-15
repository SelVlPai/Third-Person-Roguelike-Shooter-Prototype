// Fill out your copyright notice in the Description page of Project Settings.
#define COLLISION_ENEMY ECC_GameTraceChannel2

#include "EnemyBase.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Fire/UI/CW_HealthEnemy.h"
#include "Fire/Interface/InterfaceAIControllerCommon.h"
#include "Fire/Interface/InterfaceMainCharacter.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionObjectType(COLLISION_ENEMY);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel4);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	GetMesh()->SetCollisionObjectType(COLLISION_ENEMY);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	//DataAssets->MontageAttack;
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

