// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSpawnBuff.h"
#include "InterfaceDropBuff.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UACSpawnBuff::UACSpawnBuff()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACSpawnBuff::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TEveryIntervalSpawn, this, &ThisClass::BuffSpawn, Buff.Interval, true);
	// ...
	
}


// Called every frame
void UACSpawnBuff::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACSpawnBuff::ClearAndDelete()
{
	GetWorld()->GetTimerManager().ClearTimer(TEveryIntervalSpawn);
	DestroyComponent();
}

void UACSpawnBuff::BuffSpawn()
{
	//Buff.NumberSpaw--;
	if (Buff.NumberSpaw-- != 0)
	{
		ESpawnActorCollisionHandlingMethod Params = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Spawn3"));
		FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, UKismetMathLibrary::RandomPointInBoundingBox(SpawnerCollision->GetComponentTransform().GetLocation(),
			SpawnerCollision->GetScaledBoxExtent()));
		AActor* ActorBuff = GetWorld()->SpawnActorDeferred<AActor>(ClassBuff, SpawnTransform, nullptr, nullptr, Params);

		Cast<IInterfaceDropBuff>(ActorBuff)->SetInfoForBuff(Buff.InfoBuff);
		UGameplayStatics::FinishSpawningActor(ActorBuff, SpawnTransform);
	}
	else
		ClearAndDelete();
	//GetWorld()->SpawnActor(BuffClass);
	
}

