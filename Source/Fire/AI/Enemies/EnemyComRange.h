// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCommon.h"
#include "EnemyComRange.generated.h"

class UACTraceRange;
/**
 * 
 */
UCLASS()
class FIRE_API AEnemyComRange : public AEnemyCommon
{
	GENERATED_BODY()
	UPROPERTY()
	UACTraceRange* TraceRangeComponent;
public:
	AEnemyComRange();

};
