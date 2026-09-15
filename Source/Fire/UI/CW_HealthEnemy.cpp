// Fill out your copyright notice in the Description page of Project Settings.


#include "CW_HealthEnemy.h"


void UCW_HealthEnemy::UpdateHealth_Implementation(float CurrentHealth, float MaxHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, FString::Printf(TEXT("Calculate")));

}
