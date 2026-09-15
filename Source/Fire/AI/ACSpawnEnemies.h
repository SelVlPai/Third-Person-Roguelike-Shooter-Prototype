// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Fire/Data/ListEnemies.h"
#include "ACSpawnEnemies.generated.h"

class AEnemyBase;
class ASpawnerOfEnemies;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRE_API UACSpawnEnemies : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACSpawnEnemies();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TSubclassOf<AEnemyBase> ActorSpawn;
	FInfoSpawn Info;
	TArray<ASpawnerOfEnemies*> WhereSpawn;
	void StopSpawn();
		
private:
	FTimerHandle TSpawn;
	FTimerHandle TSpawnElite;
	void ToSpawnEveryInterval();
	void ToSpawnEveryIntervalElite();
};
