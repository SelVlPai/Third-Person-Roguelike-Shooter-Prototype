// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerOfEnemies.generated.h"

class UBoxComponent;

UCLASS()
class FIRE_API ASpawnerOfEnemies : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
	
public:	
	// Sets default values for this actor's properties
	ASpawnerOfEnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UBoxComponent* GetBoxCollision() { return BoxCollision; };
};
