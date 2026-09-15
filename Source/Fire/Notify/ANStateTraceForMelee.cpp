// Fill out your copyright notice in the Description page of Project Settings.


#include "ANStateTraceForMelee.h"
#include "Components/MeshComponent.h"
#include "Fire/Components/ACTraceMelee.h"
#include "Fire/Interface/InterfaceACTraceMelee.h"

//void UANStateTraceForMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Begin1")));
//	if (AActor* Character = MeshComp->GetOwner()) 
//	{
//		if (UACTraceMelee* TraceComponent = Character->FindComponentByClass<UACTraceMelee>())
//		{
//			if (TraceComponent->Implements<UInterfaceACTraceMelee>())
//			{
//				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Begin2")));
//				Cast<IInterfaceACTraceMelee>(TraceComponent)->TraceMelee(SocketBegin, SocketEnd, Radius);
//			}
//		}
//	}
//}

void UANStateTraceForMelee::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AActor* Character = MeshComp->GetOwner())
	{
		if (UACTraceMelee* TraceComponent = Character->FindComponentByClass<UACTraceMelee>())
		{
			if (TraceComponent->Implements<UInterfaceACTraceMelee>())
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Clear")));
				Cast<IInterfaceACTraceMelee>(TraceComponent)->ClearHitActors();
			}
		}
	}
}

void UANStateTraceForMelee::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Begin1")));
	if (AActor* Character = MeshComp->GetOwner())
	{
		if (UACTraceMelee* TraceComponent = Character->FindComponentByClass<UACTraceMelee>())
		{
			if (TraceComponent->Implements<UInterfaceACTraceMelee>())
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Begin2")));
				Cast<IInterfaceACTraceMelee>(TraceComponent)->TraceMelee(SocketBegin, SocketEnd, Radius);
			}
		}
	}
}
