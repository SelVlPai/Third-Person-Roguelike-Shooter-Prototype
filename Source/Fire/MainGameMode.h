// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ListEnemies.h"
#include "InterfaceGameMode.h"
#include "MainGameMode.generated.h"

class ASpawnerOfEnemies;
class AEnemyBase;
class UACSpawnEnemies;
/**
 * 
 */
UCLASS()
class FIRE_API AMainGameMode : public AGameModeBase, public IInterfaceGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly)
	UDataTable* EnemiesTable;
	UPROPERTY()
	TArray<ASpawnerOfEnemies*> Spawners;
/*	UPROPERTY()
	TMap<TSubclassOf<AEnemyBase>, FInfoSpawn> NeedSpawn;
	UPROPERTY()
	TMap<TSubclassOf<AEnemyBase>, FInfoSpawn> EnemiesOnMap;
	*/
	UPROPERTY()
	FListEnemies NeedSpawn;
	UPROPERTY()
	FListEnemies EnemiesOnMap;
	uint8 NumberWaves = 1;
	UPROPERTY()
	TArray<UACSpawnEnemies*> AllComponents;
	
	FTimerHandle TPreparingToNewWave;
	int32 MaxEnemiesOnMap;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ClassBuffsSpawner;
	AActor* BuffsSpawner;

	void StartWave();
	void NextTick();
	virtual void EnemyKilled(TSubclassOf<AEnemyBase> ClassEnemy) override;
	void PrepartionTime();
	virtual void PreparationComplete_Implementation() override;
	virtual void LaunchSavedWave(uint8 SavedNumberWave) override;
	virtual void StartWaveAfterLoading() override;
	virtual void GameModeStart() override;
};
