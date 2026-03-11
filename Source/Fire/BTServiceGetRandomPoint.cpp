// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceGetRandomPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTServiceGetRandomPoint::UBTServiceGetRandomPoint()
{
	NodeName = TEXT("Update Patrol Point");
	Interval = 1.f;
}

void UBTServiceGetRandomPoint::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (APawn* EnemyPawn = Controller->GetPawn())
		{
			FNavLocation RandomLocation;
			UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(EnemyPawn);
			NavSys->GetRandomPointInNavigableRadius(EnemyPawn->GetActorLocation(), RadiusPoint, RandomLocation);
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPointKey.SelectedKeyName, RandomLocation);
		}
	}
}
