// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TypeBuffs.generated.h"

UENUM(BlueprintType)
enum class ETypeBuffs : uint8
{
    Health,
    Armor,
    Speed
};
