// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_EnemyLow.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "InterfaceMainCharacter.h"

AAIController_EnemyLow::AAIController_EnemyLow()
{
}

void AAIController_EnemyLow::SetStrafeShoot()
{
	
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Bool - %s"), BlackBoardComponent->GetValueAsBool(TEXT("StrafeShoot")) ? TEXT("True") : TEXT("false")) );
	BlackBoardComponent->SetValueAsBool(TEXT("StrafeShoot"), true);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Bool - %s"), BlackBoardComponent->GetValueAsBool(TEXT("StrafeShoot")) ? TEXT("True") : TEXT("false")) );
}

void AAIController_EnemyLow::SetLocationNavBlock()
{
	if (Player && Player->Implements<UInterfaceMainCharacter>()) 
	{
		Cast<IInterfaceMainCharacter>(Player)->SetOnSeePlayer(true);
	}
}
