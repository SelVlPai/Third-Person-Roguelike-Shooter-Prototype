// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemiesTypes.h"
#include "PDAEnemiesCharacteristics.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UPDAEnemiesCharacteristics : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EEnemiesTypes EnemyType;
	UPROPERTY(EditAnywhere)
	float Health;
	UPROPERTY(EditAnywhere)
	float AttackRange;
	UPROPERTY(EditAnywhere)
	float AttachDamage;
	UPROPERTY(EditAnywhere)
	float RadiusCircleEQS;
	UPROPERTY(EditAnywhere)
	uint16 NumberOfPointsEQS;
	UPROPERTY(EditAnywhere)
	UAnimMontage* MontageAttack;
};
