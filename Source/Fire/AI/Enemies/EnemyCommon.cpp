// Fill out your copyright notice in the Description page of Project Settings.

#define COLLISION_PLAYER ECC_GameTraceChannel3

#include "EnemyCommon.h"
#include "Fire/UI/CW_HealthEnemy.h"
#include "Fire/Interface/InterfaceGameMode.h"
#include "GameFramework/GameMode.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Fire/AI/Controllers/AAIController_EnemyCommon.h"


AEnemyCommon::AEnemyCommon()
{
	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	WeaponStaticMesh->SetupAttachment(GetMesh());
	WeaponStaticMesh->SetCanEverAffectNavigation(false);
	WidgetHealth = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetHealth->SetupAttachment(GetRootComponent());
	WidgetHealth->SetCanEverAffectNavigation(false);

	Tags.Add(FName("CommonEnemy"));
	

}

void AEnemyCommon::BeginPlay()
{
	Super::BeginPlay();
	WeaponStaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Weapon"));
	Characteristics = DuplicateObject(Characteristics, this);
	MaxHealth = Characteristics->Health;
	Health = MaxHealth;
}

float AEnemyCommon::TakeDamage(float DamageCount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageCount;
	if (Health <= 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Damage = %f - Health = %f  DESTROY"), DamageAmount, Health));
		Cast<IInterfaceGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) )->EnemyKilled(this->GetClass());
		this->Destroy();
	}
	else
	{
		if (WidgetHealth && WidgetHealth->GetUserWidgetObject())
		{
			if (UCW_HealthEnemy* MainWidget = Cast<UCW_HealthEnemy>(WidgetHealth->GetUserWidgetObject()))
			{
				MainWidget->UpdateHealth(Health, MaxHealth);
				if (DamageCauser != nullptr)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Damage = %f - Health = %f - Name = %s"), DamageAmount, Health, *DamageCauser->GetName()));
				}
			}
		}


	};
	return DamageCount;
}

void AEnemyCommon::SetParametsForElite()
{
	Cast<AAIController_EnemyCommon>(GetController())->SetIsEliteKey();
	IsElite = true;
	SetEliteParamets();
	SetActorScale3D(FVector(1.2f));
	Characteristics->AttachDamage *= 2;
	Characteristics->AttackRange *= 2;
	Characteristics->Health *= 2;
	MaxHealth *= 2;
	Health *= 2;
	if (WidgetHealth && WidgetHealth->GetUserWidgetObject())
		Cast<UCW_HealthEnemy>(WidgetHealth->GetUserWidgetObject())->SetEliteHealthBar();
}

