// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

UCLASS()
class FIRE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TMap <uint8, uint8> ArmorInCharacter;
public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetBullet(uint8 NowBullet, uint8 MagazinBullet, const FString& MainOrSecondary);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetVisibilityBulletOfWeapon(ESlateVisibility NewVisibility, const FString& MainOrSecondary);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowRechargeWeapon(float Time);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopRecharge();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowHitMarket(bool HeadShoot);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetProgressBarHP(float NewFrontHP, float NewBackHP, float NewMaxHP);
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	//void SetArmor(TMap<uint8, float>& ArmorParam);
	UFUNCTION(BlueprintPure)
	TMap <uint8, uint8> GetArmorInCharacter() { return ArmorInCharacter; };
	UFUNCTION()
	void SetArmorInCharacter(TMap <uint8, uint8>& NewArmor, uint8 NewMaxPartsArmor, uint8 NewMaxCurrentArmor) {
		ArmorInCharacter = NewArmor;
		SetArmor(NewMaxPartsArmor, NewMaxCurrentArmor);
	};
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetArmor(uint8 MaxPartsArmorText, uint8 MaxCurrentArmorBar);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void WaveCountDownHUD(float Counting);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentWaveHUD(uint8 NumberWave);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetNumberEnemiesOnMapHUD(int32 MaxEnemies);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateCountKilledEnemyHUD();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowDamageToEnemyHUD(float Damage, bool Crit, AActor* HitActor);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ScaleAimSightHUD(float Spread);

};
