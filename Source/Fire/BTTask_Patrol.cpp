// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol(C++)");
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}
