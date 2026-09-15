// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBoss.h"
#include "Fire/UI/WidgetHPBoss.h"
#include "GameFramework/GameMode.h"
#include "Fire/AI/Controllers/AIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "Fire/Interface/InterfaceGameMode.h"
#include <Kismet/GameplayStatics.h>


AEnemyBoss::AEnemyBoss()
{
	SphereCollisionWeakPoint = CreateDefaultSubobject<USphereComponent>(TEXT("WeakPoint"));
	SphereCollisionWeakPoint->SetupAttachment(GetMesh());
	SphereCollisionWeakPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AEnemyBoss::BeginPlay()
{
	Super::BeginPlay();
	//SphereCollisionWeakPoint->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("Heart"));
	if (WidgetHPClass)
	{
		Health = MaxHealth;
		WidgetHP = Cast<UWidgetHPBoss>(CreateWidget<UUserWidget>(GetWorld(), WidgetHPClass));
		WidgetHP->MaxHealth = MaxHealth;
		WidgetHP->Name = TEXT("Boss");
		//WidgetHP->SetHealth(MaxHealth);
		WidgetHP->AddToViewport();
	}
	OverMaterWeakPoint = GetMesh()->CreateDynamicMaterialInstance(9, InterfaceWeakPoint, NAME_None);
	BlackBoardComp = Cast<AAIController_Base>(GetController())->GetBlackboardComponent();
	PhasePercent = (MaxHealth / (float)(Phase + 1)) / MaxHealth * 100.f;
	HPActiveRage = (Phase + 1) / 2 * PhasePercent;
}

float AEnemyBoss::TakeDamage(float DamageCount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageCount;
	if (Health > 0)
	{
		WidgetHP->SetHealth(Health);
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Silver, FString::Printf(TEXT("%f"), PhasePercent));
		float PercentLeft = Health / MaxHealth * 100.f;
		if (PercentLeft <= PhasePercent * Phase)
		{
			if (HPActiveRage >= PercentLeft)
			{
				BlackBoardComp->SetValueAsBool(FName("Rage"), true);
			}
			BlackBoardComp->SetValueAsBool(FName("Stun"), true);
			GetWorld()->GetTimerManager().SetTimer(TCompleteStun, this, &ThisClass::CompleteStun, 5.f, false);
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Silver, FString::Printf(TEXT("Activate")));
			//GetMesh()->GetAnimInstance()->Montage_Play(AnimationStun);
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Silver, FString::Printf(TEXT("true")));
			GetMesh()->SetOverlayMaterial(OverMaterWeakPoint);
			if (OverMaterWeakPoint)
			{
				GetMesh()->SetOverlayMaterial(OverMaterWeakPoint);
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Silver, FString::Printf(TEXT("true")));
			}
			else
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Silver, FString::Printf(TEXT("false")));
			FName SocketWeakPoint = *VulnerableZones.Find(Phase);
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Silver, FString::Printf(TEXT("%s"), *SocketWeakPoint.ToString()));
			OverMaterWeakPoint->SetVectorParameterValue(FName("WeakPointPosition"), GetMesh()->GetSocketLocation(SocketWeakPoint));
			SphereCollisionWeakPoint->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			SphereCollisionWeakPoint->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketWeakPoint);
			Phase -= 1;
		}
	}
	else
	{
		WidgetHP->RemoveFromParent();
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Before")));
		//Cast<IInterfaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->EnemyKilled(this->GetClass());
		Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("After")));
	}
	return DamageCount;
}

void AEnemyBoss::CompleteStun()
{
	GetMesh()->SetOverlayMaterial(nullptr);
	SphereCollisionWeakPoint->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	SphereCollisionWeakPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BlackBoardComp->ClearValue(FName("Stun"));
}
