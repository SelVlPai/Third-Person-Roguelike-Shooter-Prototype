// Fill out your copyright notice in the Description page of Project Settings.

#define COLLISION_PLAYER ECC_GameTraceChannel3

#include "EnemyComRange.h"
#include "Kismet/GameplayStatics.h"

AEnemyComRange::AEnemyComRange()
{
}

void AEnemyComRange::Trace(FName StartSocket, float RangeTrace)
{
	USkeletalMeshComponent* MeshComp = GetMesh();
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Line1")));
	if (MeshComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Line2")));
		FVector Start = MeshComp->GetSocketLocation(StartSocket);
		FVector End = Start + FMath::VRandCone(GetActorForwardVector(), FMath::DegreesToRadians(FMath::FRandRange(2.f, 5.f))) * RangeTrace;
		FCollisionQueryParams IgnoreActors;
		IgnoreActors.AddIgnoredActor(this);
		FHitResult Result;
		FCollisionObjectQueryParams HitActors;
		HitActors.AddObjectTypesToQuery(COLLISION_PLAYER);

		if (GetWorld()->LineTraceSingleByObjectType(Result, Start, End, HitActors, IgnoreActors))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Line3")));
			if (Result.GetActor())
			{
				UGameplayStatics::ApplyDamage(Result.GetActor(), Characteristics->AttachDamage, GetController(), this, UDamageType::StaticClass());
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("%f"), Characteristics->AttachDamage));
			}
		}
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f, 0, 2.f);
	}
}

/*void AEnemyComRange::AIAttack(UAnimMontage* Attack, FSimpleDelegate OnFinished)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Range")));
	OnFinished.ExecuteIfBound();
	//GetParentActor()->GetParentActor()
}*/
