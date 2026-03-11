// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyLineTrace.h"
#include "InterfaceEnemyCommon.h"
#include "Components/MeshComponent.h"

void UAnimNotifyLineTrace::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AActor* Character = MeshComp->GetOwner()) 
	{
		if (Character->Implements<UInterfaceEnemyCommon>()) 
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Notify")));
			Cast<IInterfaceEnemyCommon>(Character)->Trace(Socket, Range);
		}
	}
}
