// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceBuffSpawner.h"
#include "SpawnerOfBaffs.generated.h"

class UBoxComponent;
class UACSpawnBuff;

UCLASS()
class FIRE_API ASpawnerOfBaffs : public AActor, public IInterfaceBuffSpawner
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
	


public:	
	// Sets default values for this actor's properties
	ASpawnerOfBaffs();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//UPROPERTY()
	//ADropsBuff* Buff;
	TArray<FName> RowsInTable;
	UPROPERTY(EditDefaultsOnly)
	UDataTable* TableBuffs;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ClassDropBuff;
	TArray<UACSpawnBuff*> AllACBuffs;

	virtual void SpawnBuffs(uint8 NumberWave) override;
	virtual void ClearSpawn() override;

};
