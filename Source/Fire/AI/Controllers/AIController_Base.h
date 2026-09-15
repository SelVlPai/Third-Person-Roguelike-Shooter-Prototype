// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Base.generated.h"
 
class UPDAEnemiesCharacteristics;

UCLASS(Abstract)
class FIRE_API AAIController_Base : public AAIController
{
	GENERATED_BODY()

public:
	AAIController_Base();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBlackboardData* BlackBoardAsset;

	UBlackboardComponent* BlackBoardComponent;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	ACharacter* Player;
	UPROPERTY()
	UPDAEnemiesCharacteristics* EnemyCharac;
};
