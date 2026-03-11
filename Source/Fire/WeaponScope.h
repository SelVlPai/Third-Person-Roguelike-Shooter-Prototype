// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponScope.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class ENameScopes : uint8
{
	None,
	IronSight, //   UMETA(DisplayName = "Iron Sight"),
	RedDot,    //   UMETA(DisplayName = "Red Dot"),
	Holo,      //   UMETA(DisplayName = "Holographic"),
	Zoom4x,     //  UMETA(DisplayName = "4x Scope"),
	Zoom8x,     //  UMETA(DisplayName = "8x Scope"),
	Zoom12x     // UMETA(DisplayName = "12x Scope")
};

USTRUCT(BlueprintType)
struct FWeaponScope : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENameScopes ScopeName = ENameScopes::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimFOV = 80.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LocationForAim = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RotationForAim = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AimTime = 0.15f;
};

USTRUCT(BlueprintType)
struct FVisualParametersScope : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENameScopes ScopeName = ENameScopes::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture = nullptr;
	bool operator==(const FVisualParametersScope& Other) const
	{
		return ScopeName == Other.ScopeName
			&& StaticMesh == Other.StaticMesh
			&& Texture == Other.Texture;
	}
};