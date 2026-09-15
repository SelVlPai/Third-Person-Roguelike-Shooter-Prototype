// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMoveToNavBlock.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Fire/Interface/InterfaceAIControllerCommon.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMoveToNavBlock::UBTTaskMoveToNavBlock()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTaskMoveToNavBlock::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	FAIMoveRequest MoveRequest;
	AIControl = OwnerComponent.GetAIOwner();
	//AAIController* AIControl = OwnerComponent.GetAIOwner();
	UBlackboardComponent* BlackBoard = AIControl->GetBlackboardComponent();
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Start")));


	//if (TargetKey.IsSet())
	//{
	MoveComplete = false;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Start")));
	FVector TargetLocation = BlackBoard->GetValueAsVector(TargetKey.SelectedKeyName);
	if (TargetLocation.IsZero())  // або TargetLocation == FVector::ZeroVector
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("TargetLocation not set!"));
		return EBTNodeResult::Failed;
	}
	MoveRequest.SetGoalLocation(TargetLocation);
	MoveRequest.SetAcceptanceRadius(AcceptableRadius);
	FNavPathSharedPtr Path;
	EPathFollowingRequestResult::Type Result = AIControl->MoveTo(MoveRequest, &Path);
	GetWorld()->GetTimerManager().SetTimer(TSetLocNavBlock, this, &ThisClass::SetLocation, TimeTick, true);
	if (Result == EPathFollowingRequestResult::Failed)
		return EBTNodeResult::Failed;
	else if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
		return EBTNodeResult::Succeeded;
	MoveCompleteHandle = AIControl->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ThisClass::OnMoveCompleted, &OwnerComponent);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("InProgress")));
	return EBTNodeResult::InProgress;
	//}
	//else return EBTNodeResult::Failed;
}

void UBTTaskMoveToNavBlock::SetLocation()
{
	if (!MoveComplete)
	{
		/*GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Set")));
		if (AIControl && AIControl->Implements<UInterfaceAIController>())
			Cast<IInterfaceAIController>(AIControl)->SetLocationNavBlock();*/
	}
	else GetWorld()->GetTimerManager().ClearTimer(TSetLocNavBlock);
}

void UBTTaskMoveToNavBlock::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result, UBehaviorTreeComponent* OwnerComp)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Complete")));

	if (!OwnerComp)
		return;

	EBTNodeResult::Type BTResult =
		Result.IsSuccess() ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	MoveComplete = true;
	FinishLatentTask(*OwnerComp, BTResult);
}



void UBTTaskMoveToNavBlock::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("finish")));

	if (AAIController* AICon = OwnerComp.GetAIOwner())
	{
		if (AICon->GetPathFollowingComponent())
		{
			AICon->GetPathFollowingComponent()
				->OnRequestFinished.Remove(MoveCompleteHandle);
		}
	}
}


