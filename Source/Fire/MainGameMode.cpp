// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "SpawnerOfEnemies.h"
#include "EngineUtils.h"
#include "EnemyBase.h"
#include "SaveGamePlayerInfo.h"
#include "InterfacePlayerController.h"
#include "InterfaceBuffSpawner.h"
#include "InterfaceMainCharacter.h"
#include "MainGameInstance.h"
#include "ACSpawnEnemies.h"
#include <Kismet/GameplayStatics.h>

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<ASpawnerOfEnemies> It(GetWorld()); It; ++It)
	{
		ASpawnerOfEnemies* Spawner = *It;
		Spawners.Add(Spawner);
	}
	BuffsSpawner = UGameplayStatics::GetActorOfClass(GetWorld(), ClassBuffsSpawner);
	if(UMainGameInstance* GI = Cast<UMainGameInstance>(GetGameInstance()))
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Valid"));
	else
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("NotValid"));

	//StartWave();
	//GetWorld()->GetTimerManager().SetTimerForNextTick();
	GetWorldTimerManager().SetTimerForNextTick(this, &ThisClass::GameModeStart);
}

void AMainGameMode::StartWave()
{
	TArray<FName> Rows;
	if (EnemiesTable)
	{
		Cast<IInterfaceBuffSpawner>(BuffsSpawner)->SpawnBuffs(NumberWaves - 1);
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Start 1"));
		FListEnemies* Row = EnemiesTable->FindRow<FListEnemies>(EnemiesTable->GetRowNames()[NumberWaves - 1], TEXT("Falied Row"));
		EnemiesOnMap = *Row;
		NeedSpawn = *Row;
		for (int32 i = 0; i < NeedSpawn.List.Num(); i++)
		{
			UACSpawnEnemies* NewComp = NewObject<UACSpawnEnemies>(this);
			AllComponents.Add(NewComp);
			NewComp->ActorSpawn = NeedSpawn.List[i].Enemy;
			NewComp->Info = NeedSpawn.List[i].InfoEnemy;
			NewComp->WhereSpawn = Spawners;
			NewComp->RegisterComponent();
			MaxEnemiesOnMap += EnemiesOnMap.List[i].InfoEnemy.NumberEnemies;
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Start 2"));

		}
		Cast<IInterfacePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetNumberEnemiesOnMap(MaxEnemiesOnMap);
	}
}

void AMainGameMode::NextTick()
{
	
}

void AMainGameMode::EnemyKilled(TSubclassOf<AEnemyBase> ClassEnemy)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Killed1"));
	for (int32 i = 0; i < EnemiesOnMap.List.Num(); i++)
	{
		if (EnemiesOnMap.List[i].Enemy.Get() == ClassEnemy.Get())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Killed2"));
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			--EnemiesOnMap.List[i].InfoEnemy.NumberEnemies;
			Cast<IInterfacePlayerController>(PC)->UpdateCountKilledEnemy();
			if (EnemiesOnMap.List[i].InfoEnemy.NumberEnemies == 0)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Killed2"));
				EnemiesOnMap.List.RemoveAt(i);
				if (EnemiesOnMap.List.IsEmpty())
				{
					IInterfacePlayerController* InterPlayerController = Cast<IInterfacePlayerController>(PC);
					InterPlayerController->SetNumberEnemiesOnMap(0);
					++NumberWaves;
					Cast<IInterfacePlayerController>(PC)->SetCurrentWave(NumberWaves);
					InterPlayerController->WaveCountDown(3.f);
					//USaveGamePlayerInfo* SaveGameInstance = Cast<USaveGamePlayerInfo>(UGameplayStatics::CreateSaveGameObject(USaveGamePlayerInfo::StaticClass()));
					ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
					FSavePlayerInfo InfoForPlayer;
					InfoForPlayer.PositionPlayer = Player->GetTransform();
					IInterfaceMainCharacter* InterCharacter = Cast<IInterfaceMainCharacter>(Player);
					InfoForPlayer.StatsPlayer = InterCharacter->GetAllStats();
					InfoForPlayer.MainWeapon = InterCharacter->GetMainWeapon();
					InfoForPlayer.SecondWeapon = InterCharacter->GetSecondWeapon();
					InfoForPlayer.SavedCurrentWave = NumberWaves;
					//SaveGameInstance->SetAllInfo(InfoForPlayer);
					Cast<UMainGameInstance>(GetGameInstance())->SaveWave(InfoForPlayer);
					//UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("EndWaveSave"), 0);
					//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Killed3"));
					//GetWorld()->GetTimerManager().SetTimer(TPreparingToNewWave, this, &ThisClass::PrepartionTime, 7.f, false);
					Cast<IInterfaceBuffSpawner>(BuffsSpawner)->ClearSpawn();
				}
			}
		}
	}
}

//void AMainGameMode::PrepartionTime()
//{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("New Wave"));
	//MaxEnemiesOnMap = 0;
	//StartWave();
	//GetWorld()->GetTimerManager().ClearTimer(TPreparingToNewWave);
//}

void AMainGameMode::PreparationComplete_Implementation()
{
	//++NumberWaves;

	MaxEnemiesOnMap = 0;
	AllComponents.Empty();
	StartWave();

}

void AMainGameMode::LaunchSavedWave(uint8 SavedNumberWave)
{
	NumberWaves = SavedNumberWave;
	for (UACSpawnEnemies* Comp : AllComponents)
		if (IsValid(Comp))
			Comp->StopSpawn();
	AllComponents.Empty();
	
}

void AMainGameMode::StartWaveAfterLoading()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("AfterLoading 1"));

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC && PC->Implements<UInterfacePlayerController>())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("AfterLoading 2"));

		Cast<IInterfacePlayerController>(PC)->WaveCountDown(5.f);
		Cast<IInterfacePlayerController>(PC)->SetCurrentWave(NumberWaves);
	}
}

void AMainGameMode::GameModeStart()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC && PC->Implements<UInterfacePlayerController>())
	{
		Cast<IInterfacePlayerController>(PC)->WaveCountDown(5.f);
		Cast<IInterfacePlayerController>(PC)->SetCurrentWave(NumberWaves);
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		FSavePlayerInfo InfoForPlayer;
		InfoForPlayer.PositionPlayer = Player->GetTransform();
		IInterfaceMainCharacter* InterCharacter = Cast<IInterfaceMainCharacter>(Player);
		InfoForPlayer.StatsPlayer = InterCharacter->GetAllStats();
		InfoForPlayer.MainWeapon = InterCharacter->GetMainWeapon();
		InfoForPlayer.SecondWeapon = InterCharacter->GetSecondWeapon();
		InfoForPlayer.SavedCurrentWave = NumberWaves;
		//SaveGameInstance->SetAllInfo(InfoForPlayer);
		Cast<UMainGameInstance>(GetGameInstance())->SaveWave(InfoForPlayer);
	}
}
