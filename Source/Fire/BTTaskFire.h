// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskFire.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UBTTaskFire : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskFire();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;
	void FireGun();
	UPROPERTY(EditAnywhere)
	uint8 NeedShoots;
private:
	FTimerHandle TShoot;
	float LastFireTime;
	uint8 CurrentShots;
	ACharacter* EnemyCharacter = nullptr;
	FVector PlayerLocation;
	UBehaviorTreeComponent* Owner;

	
};
