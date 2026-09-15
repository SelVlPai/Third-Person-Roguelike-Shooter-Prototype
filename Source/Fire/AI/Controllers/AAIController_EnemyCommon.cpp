// Fill out your copyright notice in the Description page of Project Settings.


#include "AAIController_EnemyCommon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Fire/Interface/InterfaceMainCharacter.h"
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>
#include "Fire/Interface/InterfaceEnemyCommon.h"
#include "Fire/Data/PDAEnemiesCharacteristics.h"

AAIController_EnemyCommon::AAIController_EnemyCommon()
{
}

void AAIController_EnemyCommon::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	EnemyCharac = Cast<IInterfaceEnemyCommon>(InPawn)->GetCharacteristics();
	if (BlackBoardComponent)
	{
		BlackBoardComponent->SetValueAsEnum(TEXT("EnemyType"), (uint8)EnemyCharac->EnemyType);
		BlackBoardComponent->SetValueAsFloat(TEXT("RadiusAttack"), EnemyCharac->AttackRange);
		BlackBoardComponent->SetValueAsFloat(TEXT("RadiusCircle"), EnemyCharac->RadiusCircleEQS);
		BlackBoardComponent->SetValueAsInt(TEXT("NumberPointsForAttack"), EnemyCharac->NumberOfPointsEQS);
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, UEnum::GetValueAsString((EEnemiesTypes)BlackBoardComponent->GetValueAsEnum(TEXT("EnemyType"))));
		if (EnemyCharac->MontageAttack)
			BlackBoardComponent->SetValueAsObject(TEXT("AttackMontage"), EnemyCharac->MontageAttack);
		if (Cast<IInterfaceEnemyCommon>(InPawn)->GetIsElite())
			BlackBoardComponent->SetValueAsBool(TEXT("IsElite"), true);
		

	}
	RunBehaviorTree(BehaviorTree);
	if (Player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Valid"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("NotValid"));
	}
	SetFocus(Player);
}

void AAIController_EnemyCommon::SetIsEliteKey()
{
	BlackBoardComponent->SetValueAsBool(TEXT("IsElite"), true);
	BlackBoardComponent->SetValueAsFloat(TEXT("RadiusAttack"), EnemyCharac->AttackRange * 2);

}
//void AAIController_EnemyLow::SetLocationNavBlock()
//{
//	if (Player && Player->Implements<UInterfaceMainCharacter>()) 
//	{
//		Cast<IInterfaceMainCharacter>(Player)->SetOnSeePlayer(true);
//	}
//}
