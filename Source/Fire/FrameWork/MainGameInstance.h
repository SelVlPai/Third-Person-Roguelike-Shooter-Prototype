// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Fire/SaveGame/SaveGamePlayerInfo.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY()
	USaveGamePlayerInfo* SaveGamePlayer;
	FString SlotName;

public:
	void SaveWave(const FSavePlayerInfo& Info);
	const FSavePlayerInfo* GetSaveWave();
	virtual void Init() override;
	
};
