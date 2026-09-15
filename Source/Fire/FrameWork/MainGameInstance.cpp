// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "Fire/Interface/InterfaceMainCharacter.h"


void UMainGameInstance::Init()
{
	SlotName = "SaveWaveEnd";
#if WITH_EDITOR
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UGameplayStatics::DeleteGameInSlot(SlotName, 0);
	}

#endif 

	SaveGamePlayer = Cast<USaveGamePlayerInfo>(UGameplayStatics::CreateSaveGameObject(USaveGamePlayerInfo::StaticClass()));
	//SetValueSaveGame();
}

void UMainGameInstance::SaveWave(const FSavePlayerInfo& Info)
{
	SaveGamePlayer->SetAllInfo(Info);
	UGameplayStatics::SaveGameToSlot(SaveGamePlayer, SlotName, 0);
}

const FSavePlayerInfo* UMainGameInstance::GetSaveWave()
{
	if (SaveGamePlayer)
		return &SaveGamePlayer->GetAllInfo();
	return nullptr;
}


