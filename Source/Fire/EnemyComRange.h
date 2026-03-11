// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCommon.h"
#include "EnemyComRange.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API AEnemyComRange : public AEnemyCommon
{
	GENERATED_BODY()
public:
	AEnemyComRange();
	//virtual void AIAttack(UAnimMontage* Attack, FSimpleDelegate OnFinished) override;
	void Trace(FName StartSocket, float RangeTrace) override;
private:
};
