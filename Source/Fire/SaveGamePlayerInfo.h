// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerInfo.h"
#include "SaveGamePlayerInfo.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API USaveGamePlayerInfo : public USaveGame
{
	GENERATED_BODY()
	UPROPERTY()
	FSavePlayerInfo AllInfo;
public:
	const FSavePlayerInfo& GetAllInfo() const { return AllInfo; };
	void SetAllInfo(const FSavePlayerInfo& Info) 
	{
		AllInfo.MainWeapon = Info.MainWeapon;
		AllInfo.SecondWeapon = Info.SecondWeapon;
		AllInfo.PositionPlayer = Info.PositionPlayer;
		AllInfo.StatsPlayer = Info.StatsPlayer;
		AllInfo.SavedCurrentWave = Info.SavedCurrentWave;
	};
};
