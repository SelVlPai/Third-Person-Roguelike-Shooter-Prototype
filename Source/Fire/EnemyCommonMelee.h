// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCommon.h"
#include "EnemyCommonMelee.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API AEnemyCommonMelee : public AEnemyCommon
{
	GENERATED_BODY()
public:
	AEnemyCommonMelee();
	virtual void Trace(FName StartSocket, FName EndSocket) override;
	virtual void TraceClear() override;
private:
	FName SocketBegin;
	FName SocketEnd;
	FTimerHandle TTraceSweep;
	void TraceMelee();

	bool HitToPlayer;
};
