// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InterfaceWChooseSights.h"
#include "ChooseSight.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UChooseSight : public UUserWidget, public IInterfaceWChooseSights
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintImplementableEvent)
	//virtual void ShowChooseSights_Implementation(AActor* OwnerActor, ENameScopes NameScope, UTexture2D* TextureSight) override;
};
