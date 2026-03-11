// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyBoss.generated.h"

class UWidgetHPBoss;
class USphereComponent;
/**
 * 
 */
UCLASS()
class FIRE_API AEnemyBoss : public AEnemyBase
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollisionWeakPoint;
	
public:
	AEnemyBoss();
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageCount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
private:
	FTimerHandle TCompleteStun;
	void CompleteStun();

protected:
	UPROPERTY()
	UWidgetHPBoss* WidgetHP;
	UPROPERTY()
	UMaterialInstanceDynamic* OverMaterWeakPoint;


	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AnimationStun;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* InterfaceWeakPoint;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWidgetHPBoss> WidgetHPClass;
	uint8 Phase = 3;
	// вразлива зона { uint - стадія  FName - кість}
	UPROPERTY(EditDefaultsOnly)
	TMap<uint8, FName> VulnerableZones
	{
		{3, "Heart"},
		{2, "None" },
		{1, "None"}
	};
};
