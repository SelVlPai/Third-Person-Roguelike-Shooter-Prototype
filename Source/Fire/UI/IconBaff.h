// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IconBaff.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UIconBaff : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetTexture(UTexture2D* Icon);
	UFUNCTION(BlueprintImplementableEvent)
	void SetDistance(float Distance);
};
