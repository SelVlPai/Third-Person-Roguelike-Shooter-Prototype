// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Fire/Interface/InterfaceACTraceMelee.h"
#include "ACTraceMelee.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRE_API UACTraceMelee : public UActorComponent, public IInterfaceACTraceMelee
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACTraceMelee();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void ClearHitActors() override;
	virtual void TraceMelee(FName Begin, FName End, float Radius) override;
private:
	UPROPERTY()
	TArray<AActor*> AlreadyHitActors;
};
