// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "AIController_Base.generated.h"
 
class UPDAEnemiesCharacteristics;

UCLASS(Abstract)
class FIRE_API AAIController_Base : public AAIController
{
	GENERATED_BODY()

public:
	AAIController_Base();

	void SetIsEliteKey();
protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAIPerceptionComponent* Perception;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBlackboardData* BlackBoardAsset;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UBlackboardComponent* BlackBoardComponent;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
	AActor* Player;

	UPDAEnemiesCharacteristics* EnemyCharac;
};
