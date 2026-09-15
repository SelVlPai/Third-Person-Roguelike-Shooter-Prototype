// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyLineTrace.h"
#include "Fire/Interface/InterfaceACTraceRange.h"
#include "Fire/Components/ACTraceRange.h"
#include "Components/MeshComponent.h"

void UAnimNotifyLineTrace::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AActor* Character = MeshComp->GetOwner()) 
	{
		if (UACTraceRange* TraceComponent = Character->FindComponentByClass<UACTraceRange>())
		{
			if (TraceComponent->Implements<UInterfaceACTraceRange>())
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("Begin2")));
				Cast<IInterfaceACTraceRange>(TraceComponent)->TraceRange(SocketBegin, RangeTrace);
			}
		}
	}
}
