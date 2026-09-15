// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire/Buffs/TypeBuffs.h"
#include "PDAInfoAboutBuff.generated.h"

/**
 * 
 */
UCLASS()
class FIRE_API UPDAInfoAboutBuff : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	ETypeBuffs NameBuff;

	UPROPERTY(EditAnywhere)
	float AddingCurrentBuff;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

};


