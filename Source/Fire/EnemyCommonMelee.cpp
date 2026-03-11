// Fill out your copyright notice in the Description page of Project Settings.

#define COLLISION_PLAYER ECC_GameTraceChannel3 

#include "EnemyCommonMelee.h"
#include "Kismet/GameplayStatics.h"

AEnemyCommonMelee::AEnemyCommonMelee()
{
}

void AEnemyCommonMelee::Trace(FName StartSocket, FName EndSocket)
{
	SocketBegin = StartSocket;
	SocketEnd = EndSocket;
	GetWorld()->GetTimerManager().SetTimer(TTraceSweep, this, &ThisClass::TraceMelee, 0.02f, true);
}

void AEnemyCommonMelee::TraceMelee()
{
	USkeletalMeshComponent* MeshComp = GetMesh();
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Sweep1")));
	if (MeshComp)
	{
		FVector Start = MeshComp->GetSocketLocation(SocketBegin);
		FVector End = MeshComp->GetSocketLocation(SocketEnd);
		FCollisionQueryParams IgnoreActors;
		IgnoreActors.AddIgnoredActor(this);
		FHitResult Result;
		FCollisionObjectQueryParams HitActors;
		HitActors.AddObjectTypesToQuery(COLLISION_PLAYER);
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Sweep2")));
		if (GetWorld()->SweepSingleByObjectType(Result, Start, End, FQuat::Identity, HitActors,
			FCollisionShape::MakeCapsule(40.f, 10.f), IgnoreActors))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Sweep3")));
			if (Result.GetActor() && !HitToPlayer)
			{
				HitToPlayer = true;
				UGameplayStatics::ApplyDamage(Result.GetActor(), Characteristics->AttachDamage, GetController(), this, UDamageType::StaticClass());
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, FString::Printf(TEXT("%f"), Characteristics->AttachDamage));
			}
		}

		DrawDebugCapsule(GetWorld(), Start, 40.f, 10.f, FQuat::Identity, FColor::Red, false, 1.f);
		DrawDebugCapsule(GetWorld(), End, 40.f, 10.f, FQuat::Identity, FColor::Red, false, 1.f);
	}
}

void AEnemyCommonMelee::TraceClear()
{
	HitToPlayer = false;
	GetWorld()->GetTimerManager().ClearTimer(TTraceSweep);
}

/*void AEnemyCommonMelee::AIAttack(UAnimMontage* Attack, FSimpleDelegate OnFinished)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Melee")));
	OnFinished.ExecuteIfBound();
	//FOnMontageEnded EndDelegate;
}*/
