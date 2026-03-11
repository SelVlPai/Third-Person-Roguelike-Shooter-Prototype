// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfaceGameMode.generated.h"

class AEnemyBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceGameMode : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIRE_API IInterfaceGameMode
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void EnemyKilled(TSubclassOf<AEnemyBase> ClassEnemy) = 0;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PreparationComplete();
	virtual void LaunchSavedWave(uint8 SavedNumberWave) = 0;
	virtual void StartWaveAfterLoading() = 0;
	virtual void GameModeStart() = 0;
};
