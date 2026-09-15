// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TypeBuffs.h"
#include "Fire/Interface/InterfaceDropBuff.h"
#include "DropsBuff.generated.h"
class USphereComponent;
class UPDAInfoAboutBuff;
class UWidgetComponent;
class UIconBaff;
UCLASS()
class FIRE_API ADropsBuff : public AActor, public IInterfaceDropBuff
{
	GENERATED_BODY()
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetIcon;
public:	
	// Sets default values for this actor's properties
	ADropsBuff();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

	UPROPERTY(EditInstanceOnly)
	UPDAInfoAboutBuff* InfoBaff;

	FTimerHandle TSetDistance;
	void SetDistance();
	ACharacter* Player;
	APlayerCameraManager* PlayerCamera;
	UIconBaff* UserWidgetIcon;

	virtual void SetInfoForBuff(UPDAInfoAboutBuff* AllInfoForBuff) override;

public:	

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OverlapActor, UPrimitiveComponent* OtherActor,
		int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
