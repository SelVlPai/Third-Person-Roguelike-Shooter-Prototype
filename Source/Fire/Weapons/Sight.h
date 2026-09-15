// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fire/Data/WeaponScope.h"
#include "PickUpDrop.h"
#include "Sight.generated.h"
class UStaticMeshComponent;
class USphereComponent;
UCLASS()
class FIRE_API ASight : public AActor, public IPickUpDrop
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASight();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVisualParametersScope SightVisual;
	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OverlapActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool FromSweep, const FHitResult& SweepResult);
	virtual FVisualParametersScope PickUpItem() override;
private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SightMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MarkerForSight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (ExposeOnSpawn = "true"))
	FDataTableRowHandle SightingTable;

	
};
