// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskAttackCommon.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UBTTaskAttackCommon : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskAttackCommon();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector MontageAttack;
	void OnAttackFinished(UBehaviorTreeComponent* OwnerComp);
};
