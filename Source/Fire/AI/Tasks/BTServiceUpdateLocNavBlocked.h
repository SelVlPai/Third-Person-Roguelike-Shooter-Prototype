// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceUpdateLocNavBlocked.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UBTServiceUpdateLocNavBlocked : public UBTService
{
	GENERATED_BODY()
public:
	UBTServiceUpdateLocNavBlocked();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
};
