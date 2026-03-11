// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemiesTypes.h"
#include "PDAEnemiesCharacteristics.h"
#include "InterfaceMainCharacter.h"
#include "InterfaceEnemyCommon.h"
#include <Kismet/GameplayStatics.h>

AAIController_Base::AAIController_Base()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	Perception->ConfigureSense(*SightConfig);
	Perception->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdate);

}

void AAIController_Base::SetIsEliteKey()
{
	BlackBoardComponent->SetValueAsBool(TEXT("IsElite"), true);
	BlackBoardComponent->SetValueAsFloat(TEXT("RadiusAttack"), EnemyCharac->AttackRange * 2);
	
}


void AAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UseBlackboard(BlackBoardAsset, BlackBoardComponent);
	EnemyCharac = Cast<IInterfaceEnemyCommon>(InPawn)->GetCharacteristics();
	if (BlackBoardComponent)
	{
		BlackBoardComponent->SetValueAsEnum(TEXT("EnemyType"), (uint8)EnemyCharac->EnemyType);
		BlackBoardComponent->SetValueAsFloat(TEXT("RadiusAttack"), EnemyCharac->AttackRange);
		BlackBoardComponent->SetValueAsFloat(TEXT("RadiusCircle"), EnemyCharac->RadiusCircleEQS);
		BlackBoardComponent->SetValueAsInt(TEXT("NumberPointsForAttack"), EnemyCharac->NumberOfPointsEQS);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, UEnum::GetValueAsString((EEnemiesTypes)BlackBoardComponent->GetValueAsEnum(TEXT("EnemyType"))));
		if (EnemyCharac->MontageAttack)
			BlackBoardComponent->SetValueAsObject(TEXT("AttackMontage"), EnemyCharac->MontageAttack);
		if(Cast<IInterfaceEnemyCommon>(InPawn)->GetIsElite())
			BlackBoardComponent->SetValueAsBool(TEXT("IsElite"), true);
		Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		BlackBoardComponent->SetValueAsObject(TEXT("Target"), Player);

	}
	RunBehaviorTree(BehaviorTree);
	SetFocus(Player);
}

void AAIController_Base::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
}