// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire/AI/Controllers/AIController_Base.h"
#include "AIController_EnemyBoss.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API AAIController_EnemyBoss : public AAIController_Base
{
	GENERATED_BODY()
public:
	AAIController_EnemyBoss();

	virtual void OnPossess(APawn* InPawn) override;
};
