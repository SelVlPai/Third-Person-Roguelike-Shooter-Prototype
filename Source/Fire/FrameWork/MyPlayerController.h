// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Fire/Interface/InterfacePlayerController.h"
#include "Fire/UI/HUDWidget.h"
#include "MyPlayerController.generated.h"

class ULoadingScreen;
/**
 * 
 */
UCLASS()
class FIRE_API AMyPlayerController : public APlayerController, public IInterfacePlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	UHUDWidget* HUDWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UHUDWidget> HUDWidgetClass;

	virtual void BeginPlay() override;
	UPROPERTY()
	FTimerHandle Timer;
	

public:
	
	virtual void SetBulletInHUD(uint8 BulletNow, uint8 BulletInMagazin, const FString& MainOrSecondary) override;
	// void SetBull(uint8 now, uint8 mag, FString mainorSecond);
	virtual void SetVisibilityBullet(ESlateVisibility NewVisibility, const FString& MainOrSecondary) override;

	virtual void RechargeShow(float TimeForRecharge) override;
	virtual void StopRecharge() override;
	virtual void ShowHitMarkerInHUD(bool HeadShoot) override;
	virtual void SetHPInHUD(float SetFrontHP, float SetBackHP, float SetMaxHP) override;
	virtual void SetArmorInHUD(TMap<uint8, uint8>& SetArmor, uint8 NewMaxPartsArmor, uint8 NewMaxCurrentArmor) override;
	virtual void WaveCountDown(float Counting) override;
	virtual void SetCurrentWave(uint8 NumberWave) override;
	virtual void SetNumberEnemiesOnMap(int32 MaxEnemies) override;
	virtual void UpdateCountKilledEnemy() override;
	virtual void CreateLoadingWidget() override;
	virtual void ShowDamageToEnemy(float Damage, bool Crit, AActor* HitActor) override;
	virtual void ScaleAimSight(float SpreadAim) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULoadingScreen> WidgetLoadingClass;
	ULoadingScreen* WidgetLoading;
	UFUNCTION()
	void ClearWidgetLoading();
};
