// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponScope.h"
#include "TypeBuffs.h"
#include "PlayerInfo.h"
#include "InterfaceMainCharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterfaceMainCharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIRE_API IInterfaceMainCharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetSightEquiped(FVisualParametersScope ChangeSightOnOther);
	virtual UAnimInstance* GetMesh1PInstanse() = 0;
	virtual bool GetInSight() = 0;
	virtual void ActivateBuff(ETypeBuffs Buff, float AddNumberBuff) = 0;
	virtual void SetOnSeePlayer(bool OnSeePlayer) = 0;
	virtual FStatsStruct GetAllStats() = 0;
	virtual FInfoForWeapon GetMainWeapon() = 0;
	virtual FInfoForWeapon GetSecondWeapon() = 0;

};
