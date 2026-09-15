// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceGetRandomPoint.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UBTServiceGetRandomPoint : public UBTService
{
	GENERATED_BODY()
public:
	UBTServiceGetRandomPoint();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;

	UPROPERTY(EditAnywhere)
	float RadiusPoint = 1000.f;
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PatrolPointKey;
};
