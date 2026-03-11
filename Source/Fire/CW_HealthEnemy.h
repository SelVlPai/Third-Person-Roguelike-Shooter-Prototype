// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CW_HealthEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UCW_HealthEnemy : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateHealth(float CurrentHealth, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent)
	void SetEliteHealthBar();

	void UpdateHealth_Implementation(float CurrentHealth, float MaxHealth);
};
