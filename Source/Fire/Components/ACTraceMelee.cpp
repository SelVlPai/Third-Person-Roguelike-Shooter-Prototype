// Fill out your copyright notice in the Description page of Project Settings.

#define COLLISION_PLAYER ECC_GameTraceChannel3 

#include "ACTraceMelee.h"
#include <Kismet/GameplayStatics.h>
#include "Fire/Interface/InterfaceEnemyCommon.h"
#include "Fire/Data/PDAEnemiesCharacteristics.h"

// Sets default values for this component's properties
UACTraceMelee::UACTraceMelee()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACTraceMelee::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UACTraceMelee::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACTraceMelee::ClearHitActors()
{
	AlreadyHitActors.Empty();
}

void UACTraceMelee::TraceMelee(FName StartSocket, FName EndSocket, float Radius)
{
	if (GetOwner())
	{
		USkeletalMeshComponent* MeshComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Sweep1")));
		if (MeshComp)
		{
			FVector Start = MeshComp->GetSocketLocation(StartSocket);
			FVector End = MeshComp->GetSocketLocation(EndSocket);

			FVector Direction = End - Start;
			float HalfHeight = Direction.Size() * 0.5f;
			FCollisionShape Capsule = FCollisionShape::MakeCapsule(Radius, HalfHeight);

			FVector Center = Start + (Direction * 0.5f);
			FQuat CaspsuleRotation = FRotationMatrix::MakeFromZ(Direction).ToQuat();

			//RadiusTrace = 60.f;

			FCollisionQueryParams IgnoreActors;
			IgnoreActors.AddIgnoredActor(GetOwner());
			FHitResult Result;
			FCollisionObjectQueryParams HitActors;
			HitActors.AddObjectTypesToQuery(COLLISION_PLAYER);
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Sweep2")));
			if (GetWorld()->SweepSingleByObjectType(Result, Center, Center, CaspsuleRotation, HitActors,
				Capsule, IgnoreActors))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Sweep3")));
				AActor* HitActor = Result.GetActor();
				if (HitActor && !AlreadyHitActors.Contains(HitActor))
				{
					AlreadyHitActors.Add(HitActor);
					float Damage;
					if (GetOwner()->Implements<UInterfaceEnemyCommon>())
						Damage = Cast<IInterfaceEnemyCommon>(GetOwner())->GetCharacteristics()->AttachDamage;
					else
						Damage = 20;
					UGameplayStatics::ApplyDamage(Result.GetActor(), Damage, Cast<APawn>(GetOwner())->GetController(),
						GetOwner(), UDamageType::StaticClass());
					//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, FString::Printf(TEXT("%f"), Characteristics->AttachDamage));
				}
			}

			DrawDebugCapsule(GetWorld(), Center, HalfHeight, Radius, CaspsuleRotation, FColor::Red, false, 1.f);
		}
	}
}
