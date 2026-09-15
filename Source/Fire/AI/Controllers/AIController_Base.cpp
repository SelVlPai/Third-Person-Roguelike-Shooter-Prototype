// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Fire/Data/EnemiesTypes.h"
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>

AAIController_Base::AAIController_Base()
{

}


void AAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UseBlackboard(BlackBoardAsset, BlackBoardComponent);
	if (BlackBoardComponent) 
	{
		Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		BlackBoardComponent->SetValueAsObject(TEXT("Target"), Player);
	}

}