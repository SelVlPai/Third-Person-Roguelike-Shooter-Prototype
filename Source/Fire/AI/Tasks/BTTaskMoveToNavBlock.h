// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Navigation/PathFollowingComponent.h>
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMoveToNavBlock.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UBTTaskMoveToNavBlock : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMoveToNavBlock();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetKey;
	UPROPERTY(EditAnywhere)
	float TimeTick;
	UPROPERTY(EditAnywhere)
	float AcceptableRadius;

	virtual void OnTaskFinished(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		EBTNodeResult::Type TaskResult
	) override;

private:
	FDelegateHandle MoveCompleteHandle;

	void OnMoveCompleted(
		FAIRequestID RequestID,
		const FPathFollowingResult& Result,
		UBehaviorTreeComponent* OwnerComp
	);
	void SetLocation();
	FTimerHandle TSetLocNavBlock;
	AAIController* AIControl;
	bool MoveComplete;
};
