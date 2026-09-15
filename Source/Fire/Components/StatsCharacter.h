// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Fire/Data/StatsStruct.h"
#include "StatsCharacter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRE_API UStatsCharacter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsCharacter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	float FrontHealth;
	float BackHealth;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
	float AddToHPBack;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	uint8 MaxPlateArmor;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	uint8 MaxCurrentArmor;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TMap<uint8, uint8> Armor;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	// <Відсотки, ШкодаПоПластинам>
	TMap<uint8, uint8> ChoiceCurrentDamage;
	FTimerHandle TSetBack;
	ACharacter* ReferencesMainChar;

	void ReduceHealth();
	void IncreaseHealth();
	uint8 SubstractPlate(float TakedDamage);
	void InflictDamageToHeath(float Damage);

public:	
	float GetFrontHealth()const { return FrontHealth; };
	float GetBackHealth()const { return BackHealth; };

	void SetMaxHealth(float SetNewMaxHealth) {MaxHealth = SetNewMaxHealth;};
	float GetMaxHealth() const { return MaxHealth; };
	TPair<uint8, float> Test;

	uint8 GetMaxPartsArmor() const { return MaxPlateArmor; };
	uint8 GetMaxCurrentArmor()  const { return MaxCurrentArmor; };
	TMap<uint8, uint8> GetArmor() const { return Armor; };

	void InflictDamage(float DamageCurrent);
	void SetMaxPartsArmor(float NewPartsArmor) { MaxPlateArmor = NewPartsArmor; };
	void SetMaxCurrentArmor(float NewCurrentArmor) { MaxCurrentArmor = NewCurrentArmor; };
	void AddNewPlate();
	void RecoveryPlate(uint8 CurrentArmor);
	void BuffRecoveryHealth(float HP);
	void BuffRecoveryArmor(float PartsOfArmor);
	void SetAttributesPlayer(const FStatsStruct& Attributes);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
