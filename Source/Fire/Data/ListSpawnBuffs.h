// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListSpawnBuffs.generated.h"
/**
 * 
 */
class UPDAInfoAboutBuff;

USTRUCT(BlueprintType)
struct FInfoBuff
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UPDAInfoAboutBuff* InfoBuff = nullptr;
	UPROPERTY(EditAnywhere)
	int32 NumberSpaw = 0;
	UPROPERTY(EditAnywhere)
	float Interval = 0;
};

USTRUCT(BlueprintType)
struct FListSpawnBuffs : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<FInfoBuff> ListAllSpawnBuff;
	//TMap<UPDAInfoAboutBuff*, int32> ListBuffsOnWave;
	//TMap<FInfoBuff, float> ListBuffsOnWave;
	/*UPROPERTY(EditAnywhere)
	float SpawnInterval;*/
};
