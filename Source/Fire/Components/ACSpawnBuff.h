// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fire/Data/ListSpawnBuffs.h"
#include "Components/ActorComponent.h"
#include "ACSpawnBuff.generated.h"

class ADropsBuff;
class UPDAInfoAboutBuff;
class UBoxComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRE_API UACSpawnBuff : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACSpawnBuff();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FInfoBuff Buff;
	//float Interval;
	TSubclassOf<AActor> ClassBuff;
	void ClearAndDelete();
	UBoxComponent* SpawnerCollision;

private:
	void BuffSpawn();
	bool WaveProgress = true;
	UPROPERTY()
	TSubclassOf<ADropsBuff> BuffClass;

	FTimerHandle TEveryIntervalSpawn;
};
