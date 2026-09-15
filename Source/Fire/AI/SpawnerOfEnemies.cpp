// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerOfEnemies.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnerOfEnemies::ASpawnerOfEnemies()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
}

// Called when the game starts or when spawned
void ASpawnerOfEnemies::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnerOfEnemies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

