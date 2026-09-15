// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Fire/Data/PDAEnemiesCharacteristics.h"
#include "Fire/Interface/InterfaceEnemyCommon.h"
#include "EnemyCommon.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class FIRE_API AEnemyCommon : public AEnemyBase, public IInterfaceEnemyCommon
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WeaponStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetHealth;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPDAEnemiesCharacteristics* Characteristics;
	virtual UPDAEnemiesCharacteristics* GetCharacteristics() override { return Characteristics; };
	virtual void SetParametsForElite() override;
	virtual bool GetIsElite() override { return IsElite; };

	UFUNCTION(BlueprintImplementableEvent)
	void SetEliteParamets();

	bool IsElite;
	
public:
	AEnemyCommon();
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageCount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
};
