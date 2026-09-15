// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_EnemyBoss.h"
#include "GameFramework/Character.h"

AAIController_EnemyBoss::AAIController_EnemyBoss()
{
}

void AAIController_EnemyBoss::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	/*if (BlackBoardComponent) 
	{

	}*/
	RunBehaviorTree(BehaviorTree);
	if (Player) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Valid"));
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("NotValid"));
	}
	SetFocus(Player);
}
