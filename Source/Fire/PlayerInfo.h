// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatsStruct.h"
#include "InfoWeapon.h"
#include "PlayerInfo.generated.h"
/**
 * 
 */

USTRUCT()
struct FSavePlayerInfo
{
	GENERATED_BODY()
	UPROPERTY()
	FTransform PositionPlayer;
	UPROPERTY()
	FStatsStruct StatsPlayer;
	UPROPERTY()
	FInfoForWeapon MainWeapon;
	UPROPERTY()
	FInfoForWeapon SecondWeapon;
	UPROPERTY()
	uint8 SavedCurrentWave = 0;

};
