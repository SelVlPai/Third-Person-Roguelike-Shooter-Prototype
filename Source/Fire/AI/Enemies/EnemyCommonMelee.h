// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCommon.h"
#include "EnemyCommonMelee.generated.h"

class UACTraceMelee;
/**
 * 
 */
UCLASS()
class FIRE_API AEnemyCommonMelee : public AEnemyCommon
{
	GENERATED_BODY()
	UPROPERTY()
	UACTraceMelee* TraceMeleeComponent;
public:
	AEnemyCommonMelee();
};
