// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadingFinished);
/**
 * 
 */
UCLASS()
class FIRE_API ULoadingScreen : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnLoadingFinished OnLoadingFinished;
	UFUNCTION(BlueprintCallable)
	void FinishLoading();
};
