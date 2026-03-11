// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfoWeapon.generated.h"

/**
 * 
 */
USTRUCT()
struct FInfoForWeapon
{
	GENERATED_BODY()
	UPROPERTY()
	TSubclassOf<AActor> ClassWeapon;
	UPROPERTY()
	float TimeRecharge = 0;
	UPROPERTY()
	uint8 BulletInAutomaton = 0;
	UPROPERTY()
	uint8 BulletInAutomatonMagazin = 0;
	UPROPERTY()
	uint8 BulletInAutomatonMax = 0;
	UPROPERTY()
	float SpreadWhenMoving = 0; // Розброс при ходьбі
	UPROPERTY()
	float SpreadMax = 0; // Максимальний розброс
	UPROPERTY()
	float SpreadPerShoot = 0; // Розброс коли стреляєш
	UPROPERTY()
	float SpreadRecovery = 0; // Швидкість повернення розбросу до 0
	UPROPERTY()
	float GunDamage = 0;
	UPROPERTY()
	float GunShootDistance = 0;
};
