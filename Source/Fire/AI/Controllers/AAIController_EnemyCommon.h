// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController_Base.h"
#include "Fire/Interface/InterfaceAIControllerCommon.h"
#include "AAIController_EnemyCommon.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API AAIController_EnemyCommon : public AAIController_Base, public IInterfaceAIControllerCommon
{
	GENERATED_BODY()

public:
	AAIController_EnemyCommon();
	virtual void OnPossess(APawn* InPawn) override;
	void SetIsEliteKey();
};
