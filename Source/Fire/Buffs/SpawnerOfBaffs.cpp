// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerOfBaffs.h"
#include "Fire/Data/ListSpawnBuffs.h"
#include "Fire/Components/ACSpawnBuff.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnerOfBaffs::ASpawnerOfBaffs()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
}

// Called when the game starts or when spawned
void ASpawnerOfBaffs::BeginPlay()
{
	Super::BeginPlay();
	RowsInTable = TableBuffs->GetRowNames();


}

// Called every frame
void ASpawnerOfBaffs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerOfBaffs::SpawnBuffs(uint8 NumberWave)
{
	FListSpawnBuffs* FoundRow = TableBuffs->FindRow<FListSpawnBuffs>(RowsInTable[NumberWave], TEXT("Error"));
	for (FInfoBuff &Elem : FoundRow->ListAllSpawnBuff)
	{
		UACSpawnBuff* LogicSpawn = NewObject<UACSpawnBuff>(this);
		AllACBuffs.Add(LogicSpawn);
		LogicSpawn->Buff = Elem;
		//LogicSpawn->Interval = Elem.Interval;
		LogicSpawn->ClassBuff = ClassDropBuff;
		LogicSpawn->SpawnerCollision = BoxCollision;
		LogicSpawn->RegisterComponent();
	}
}

void ASpawnerOfBaffs::ClearSpawn()
{
	for (UACSpawnBuff* Elem : AllACBuffs) 
	{
		if (IsValid(Elem)) 
			Elem->ClearAndDelete();
	}
	AllACBuffs.Empty();
}

