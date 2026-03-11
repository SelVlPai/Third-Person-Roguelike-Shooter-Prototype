// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatsStruct.generated.h"

/**
 * 
 */
USTRUCT()
struct FStatsStruct
{
	GENERATED_BODY()
	UPROPERTY()
	float FrontHealth = 0;
	UPROPERTY()
	float BackHealth = 0;
	UPROPERTY()
	float MaxHealth = 0;
	UPROPERTY()
	uint8 MaxPlateArmor = 0;
	UPROPERTY()
	uint8 MaxCurrentArmor = 0;
	UPROPERTY()
	TMap<uint8, uint8> ArmorNow;
};
