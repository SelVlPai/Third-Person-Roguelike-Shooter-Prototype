// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UBTTask_Patrol : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Patrol();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	

};
