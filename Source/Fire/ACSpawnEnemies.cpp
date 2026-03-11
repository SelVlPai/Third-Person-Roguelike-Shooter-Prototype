// Fill out your copyright notice in the Description page of Project Settings.


#include "ACSpawnEnemies.h"
#include "SpawnerOfEnemies.h"
#include "Components/BoxComponent.h"
#include "InterfaceEnemyCommon.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyBase.h"

// Sets default values for this component's properties
UACSpawnEnemies::UACSpawnEnemies()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACSpawnEnemies::BeginPlay()
{
	Super::BeginPlay();
	ensureMsgf(ActorSpawn, TEXT("Pls set value ActorSpawn"));	// ...
	if(Info.NumberEnemies != 0)
	GetWorld()->GetTimerManager().SetTimer(TSpawn, this, &ThisClass::ToSpawnEveryInterval, Info.Interval, true);
	if(Info.SpawnElite && Info.NumberElite != 0)
		GetWorld()->GetTimerManager().SetTimer(TSpawnElite, this, &ThisClass::ToSpawnEveryIntervalElite, Info.IntervalEliteSpawn, true);
}


// Called every frame
void UACSpawnEnemies::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACSpawnEnemies::StopSpawn()
{
	GetWorld()->GetTimerManager().ClearTimer(TSpawn);
	DestroyComponent();
}

void UACSpawnEnemies::ToSpawnEveryInterval()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Spawn1"));
	if (!WhereSpawn.IsEmpty())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Spawn2"));
		UBoxComponent* BoxForSpawner = WhereSpawn[FMath::RandRange(0, WhereSpawn.Num()- 1)]->GetBoxCollision();
		if (BoxForSpawner && ActorSpawn)
		{
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Spawn3"));

			GetWorld()->SpawnActor<AEnemyBase>(ActorSpawn, UKismetMathLibrary::RandomPointInBoundingBox(BoxForSpawner->GetComponentTransform().GetLocation(),
				BoxForSpawner->GetScaledBoxExtent()), FRotator::ZeroRotator, Params);
			--Info.NumberEnemies;
			if (Info.NumberEnemies == 0)
			{
				GetWorld()->GetTimerManager().ClearTimer(TSpawn);
				if (!GetWorld()->GetTimerManager().IsTimerActive(TSpawnElite))
					DestroyComponent();
			}
		}
	}
}

void UACSpawnEnemies::ToSpawnEveryIntervalElite()
{
	if (!WhereSpawn.IsEmpty())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Spawn2"));
		UBoxComponent* BoxForSpawner = WhereSpawn[FMath::RandRange(0, WhereSpawn.Num() - 1)]->GetBoxCollision();
		if (BoxForSpawner && ActorSpawn)
		{
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Spawn3"));

			AEnemyBase* Enemy = GetWorld()->SpawnActor<AEnemyBase>(ActorSpawn, UKismetMathLibrary::RandomPointInBoundingBox(BoxForSpawner->GetComponentTransform().GetLocation(),
				BoxForSpawner->GetScaledBoxExtent()), FRotator::ZeroRotator, Params);
			Cast<IInterfaceEnemyCommon>(Enemy)->SetParametsForElite();
			--Info.NumberElite;
			if (Info.NumberElite == 0)
			{
				GetWorld()->GetTimerManager().ClearTimer(TSpawnElite);
				if(!GetWorld()->GetTimerManager().IsTimerActive(TSpawn))
				DestroyComponent();
			}
		}
	}
}

