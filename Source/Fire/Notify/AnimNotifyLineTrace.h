// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyLineTrace.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UAnimNotifyLineTrace : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Trace")
	FName SocketBegin;
	UPROPERTY(EditAnywhere, Category = "Trace")
	float RangeTrace = 800;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
