// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListEnemies.generated.h"

class AEnemyBase;


USTRUCT()
struct FInfoSpawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	uint16 NumberEnemies = 0;
	UPROPERTY(EditAnywhere)
	float Interval = 0;
	UPROPERTY(EditAnywhere)
	bool SpawnElite;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "SpawnElite", EditConditionHides))
	uint16 NumberElite = 0;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "SpawnElite", EditConditionHides))
	float IntervalEliteSpawn = 0;
};

USTRUCT()
struct FEnemy
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyBase> Enemy;
	UPROPERTY(EditAnywhere)
	FInfoSpawn InfoEnemy;
};

USTRUCT(BlueprintType)
struct FListEnemies : public FTableRowBase
{
	GENERATED_BODY()
public:
	//UPROPERTY()
	//TMap<TSubclassOf<AEnemyBase>, FInfoSpawn> List;
	UPROPERTY(EditAnywhere)
	TArray<FEnemy> List;
};

