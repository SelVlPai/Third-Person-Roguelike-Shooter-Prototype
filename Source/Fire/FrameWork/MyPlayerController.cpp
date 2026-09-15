// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Fire/UI/LoadingScreen.h"
#include "TimerManager.h"
#include "Fire/Interface/InterfaceGameMode.h"
#include "GameFramework/GameMode.h"
#include <Kismet/GameplayStatics.h>

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
    GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Begin"));

    //GetWorldTimerManager().SetTimer(Timer, this, &ThisClass::SetBulletInHUD, 1.0f, false, 1);
    if (HUDWidgetClass)
    {
        HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
        if (HUDWidget)
            HUDWidget->AddToViewport();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HUDWidgetClass is NULL!"));
    }
    //Cast<IInterfaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GameModeStart();
}

void AMyPlayerController::SetBulletInHUD(uint8 BulletNow, uint8 BulletInMagazin, const FString& MainOrSecondary)
{
   // GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%f"), BulletNow));
    if (HUDWidget) 
        HUDWidget->SetBullet(BulletNow, BulletInMagazin, MainOrSecondary);
}

void AMyPlayerController::SetVisibilityBullet(ESlateVisibility NewVisibility, const FString& MainOrSecondary)
{
    if(HUDWidget)
        HUDWidget->SetVisibilityBulletOfWeapon(NewVisibility, MainOrSecondary);
}

void AMyPlayerController::RechargeShow(float TimeForRecharge)
{
    if (HUDWidget)
        HUDWidget->ShowRechargeWeapon(TimeForRecharge);
}

void AMyPlayerController::StopRecharge()
{
    if (HUDWidget) 
    {
        HUDWidget->StopRecharge();
    }
}

void AMyPlayerController::ShowHitMarkerInHUD(bool HeadShoot)
{
    if (HUDWidget)
    {
        HUDWidget->ShowHitMarket(HeadShoot);
    }
}

void AMyPlayerController::SetHPInHUD(float SetFrontHP, float SetBackHP, float SetMaxHP)
{
    if (HUDWidget)
    {
        HUDWidget->SetProgressBarHP(SetFrontHP, SetBackHP, SetMaxHP);
    }
}

void AMyPlayerController::SetArmorInHUD(TMap<uint8, uint8>& SetArmor, uint8 NewMaxPartsArmor, uint8 NewMaxCurrentArmor)
{
    if (HUDWidget)
    {
        HUDWidget->SetArmorInCharacter(SetArmor, NewMaxPartsArmor, NewMaxCurrentArmor);
    }
}

void AMyPlayerController::WaveCountDown(float Counting)
{
    if (HUDWidget)
    {
        HUDWidget->WaveCountDownHUD(Counting);
    }
}

void AMyPlayerController::SetCurrentWave(uint8 NumberWave)
{
    if (HUDWidget)
    {
        HUDWidget->SetCurrentWaveHUD(NumberWave);
    }
}

void AMyPlayerController::SetNumberEnemiesOnMap(int32 MaxEnemies)
{
    if (HUDWidget)
    {
        HUDWidget->SetNumberEnemiesOnMapHUD(MaxEnemies);
    }
}

void AMyPlayerController::UpdateCountKilledEnemy()
{
    if (HUDWidget)
    {
        HUDWidget->UpdateCountKilledEnemyHUD();
    }
}

void AMyPlayerController::CreateLoadingWidget()
{
    WidgetLoading = CreateWidget<ULoadingScreen>(this, WidgetLoadingClass, TEXT("LoadingWidget"));
    WidgetLoading->OnLoadingFinished.AddDynamic(this, &ThisClass::ClearWidgetLoading);
    WidgetLoading->AddToViewport();
}

void AMyPlayerController::ShowDamageToEnemy(float Damage, bool Crit, AActor* HitActor)
{
    if (HUDWidget)
    {
        HUDWidget->ShowDamageToEnemyHUD(Damage, Crit, HitActor);
    }
}

void AMyPlayerController::ScaleAimSight(float SpreadAim)
{
    if (HUDWidget)
    {
        HUDWidget->ScaleAimSightHUD(SpreadAim);
    }
}

void AMyPlayerController::ClearWidgetLoading()
{
    //GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("AfterLoading 2"));
    WidgetLoading->RemoveFromParent();
    WidgetLoading = nullptr;
    //GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("AfterLoading Player"));
    Cast<IInterfaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->StartWaveAfterLoading();
}
