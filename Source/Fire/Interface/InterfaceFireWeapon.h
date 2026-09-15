// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire/Data/InfoWeapon.h"
#include "UObject/Interface.h"
#include "InterfaceFireWeapon.generated.h"

struct FWeaponScope;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceFireWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIRE_API IInterfaceFireWeapon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FWeaponScope GetInfoAboutScope() = 0;
	virtual void ActivateFire() = 0;
	//virtual void RechargeFireWeapon() = 0;
	virtual uint8 GetBullet() = 0;
	virtual void SetSightParametrs(UStaticMesh* SetMesh, FName SocketName) = 0;
	virtual void SetBulletWeaponHUD(FString SetCategory) = 0;
	virtual void SetVisibilityWeaponHUD() = 0;
	virtual void RechargeFire() = 0;
	virtual bool const GetIsRecharge() = 0;
	virtual void StopRechargeHUD(bool SetRecharge) = 0;
	virtual uint8 const GetBulletInAutomation() = 0;
	virtual FInfoForWeapon GetInfoForWeapon() const = 0;
	virtual void SetInfoForWeapon(const FInfoForWeapon& SetInfoWeapon) = 0;
	virtual void SetSpread(FString TypeSpread) = 0;
	virtual void RunTimerRecoverySpreadAccumulated() = 0;
};
