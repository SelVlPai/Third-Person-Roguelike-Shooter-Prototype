// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskSetMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UBTTaskSetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskSetMovementSpeed();
protected:
	UPROPERTY(EditAnywhere)
	float SetNewSpeed;
	UPROPERTY(EditAnywhere)
	bool SetOrient;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;

};
