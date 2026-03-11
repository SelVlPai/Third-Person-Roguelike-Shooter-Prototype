// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceUpdateLocNavBlocked.h"
#include "GameFramework/Character.h"
#include "InterfaceAIController.h"
#include "AIController.h"

UBTServiceUpdateLocNavBlocked::UBTServiceUpdateLocNavBlocked()
{
}

void UBTServiceUpdateLocNavBlocked::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	/*static float TimeLastUpdate = 0.f;
	TimeLastUpdate += DeltaSeconds;
	
	if (TimeLastUpdate >= 0.4f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("%f"), TimeLastUpdate));
		TimeLastUpdate = 0;*/
		if (AAIController* AIControl = OwnerComp.GetAIOwner())
			if (AIControl->Implements<UInterfaceAIController>())
				Cast<IInterfaceAIController>(AIControl)->SetLocationNavBlock();
	//}
}
