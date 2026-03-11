// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController_Base.h"
#include "InterfaceAIController.h"
#include "AIController_EnemyLow.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class FIRE_API AAIController_EnemyLow : public AAIController_Base, public IInterfaceAIController
{
	GENERATED_BODY()
public:
	AAIController_EnemyLow();
	virtual void SetStrafeShoot() override;
	virtual void SetLocationNavBlock() override;
};
