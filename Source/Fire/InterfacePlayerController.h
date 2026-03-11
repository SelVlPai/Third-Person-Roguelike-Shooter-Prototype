// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfacePlayerController.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfacePlayerController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIRE_API IInterfacePlayerController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetBulletInHUD(uint8 BulletNow, uint8 BulletInMazin, const FString& MainOrSecondary) = 0;

	virtual void SetVisibilityBullet(ESlateVisibility NewVisibility, const FString& MainOrSecondary) = 0;

	virtual void RechargeShow(float TimeForRecharge) = 0;
	virtual void StopRecharge() = 0;
	virtual void ShowHitMarkerInHUD(bool HeadShoot) = 0;
	virtual void SetHPInHUD(float SetFrontHP, float SetVackHP, float SetMaxHP) = 0;
	virtual void SetArmorInHUD(TMap<uint8, uint8>& SetArmor, uint8 NewMaxPartsArmor, uint8 NewMaxCurrentArmor) = 0;
	virtual void WaveCountDown(float Counting) = 0;
	virtual void SetCurrentWave(uint8 NumberWave) = 0;
	virtual void SetNumberEnemiesOnMap(int32 MaxEnemies) = 0;
	virtual void UpdateCountKilledEnemy() = 0;
	virtual void CreateLoadingWidget() = 0;
	virtual void ShowDamageToEnemy(float Damage, bool Crit, AActor* HitActor) = 0;
	virtual void ScaleAimSight(float SpreadAim) = 0;

};	
