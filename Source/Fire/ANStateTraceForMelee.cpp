// Fill out your copyright notice in the Description page of Project Settings.


#include "ANStateTraceForMelee.h"
#include "Components/MeshComponent.h"
#include "InterfaceEnemyCommon.h"

void UANStateTraceForMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (AActor* Character = MeshComp->GetOwner()) 
	{
		if (Character->Implements<UInterfaceEnemyCommon>()) 
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Begin")));
			Cast<IInterfaceEnemyCommon>(Character)->Trace(SocketBegin, SocketEnd);
		}
	}
}

void UANStateTraceForMelee::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AActor* Character = MeshComp->GetOwner())
	{
		if (Character->Implements<UInterfaceEnemyCommon>())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("End")));
			Cast<IInterfaceEnemyCommon>(Character)->TraceClear();
		}
	}
}
