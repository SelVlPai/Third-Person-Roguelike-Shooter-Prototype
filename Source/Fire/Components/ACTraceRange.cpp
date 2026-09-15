// Fill out your copyright notice in the Description page of Project Settings.

#define COLLISION_PLAYER ECC_GameTraceChannel3


#include "ACTraceRange.h"
#include "Fire/Data/PDAEnemiesCharacteristics.h"
#include "Fire/Interface/InterfaceEnemyCommon.h"
#include <Kismet/GameplayStatics.h>
// Sets default values for this component's properties
UACTraceRange::UACTraceRange()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACTraceRange::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UACTraceRange::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACTraceRange::TraceRange(FName Begin, float Range)
{

	USkeletalMeshComponent* MeshComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Line1")));
	if (MeshComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Line2")));
		FVector Start = MeshComp->GetSocketLocation(Begin);
		FVector End = Start + FMath::VRandCone(GetOwner()->GetActorForwardVector(), FMath::DegreesToRadians(FMath::FRandRange(2.f, 5.f))) * Range;
		FCollisionQueryParams IgnoreActors;
		IgnoreActors.AddIgnoredActor(GetOwner());
		FHitResult Result;
		FCollisionObjectQueryParams HitActors;
		HitActors.AddObjectTypesToQuery(COLLISION_PLAYER);

		if (GetWorld()->LineTraceSingleByObjectType(Result, Start, End, HitActors, IgnoreActors))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Line3")));
			if (Result.GetActor())
			{
				UPDAEnemiesCharacteristics* Characteristics = Cast<IInterfaceEnemyCommon>(GetOwner())->GetCharacteristics();
				UGameplayStatics::ApplyDamage(Result.GetActor(), Characteristics->AttachDamage, Cast<APawn>(GetOwner())->GetController(), GetOwner(),
					UDamageType::StaticClass());
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("%f"), Characteristics->AttachDamage));
			}
		}
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f, 0, 2.f);
	}

}

