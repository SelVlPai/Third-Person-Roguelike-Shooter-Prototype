// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskAttackCommon.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "InterfaceEnemyCommon.h"

UBTTaskAttackCommon::UBTTaskAttackCommon()
{
}

EBTNodeResult::Type UBTTaskAttackCommon::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	if (AAIController* AIControl = OwnerComponent.GetAIOwner()) 
	{
		if (ACharacter* Enemy = AIControl->GetCharacter())
			if (Enemy->Implements<UInterfaceEnemyCommon>()) 
			{
				if (AIControl->GetBlackboardComponent()->GetValueAsObject(MontageAttack.SelectedKeyName))
				{
					UAnimMontage* Montage = Cast<UAnimMontage>(AIControl->GetBlackboardComponent()->GetValueAsObject(MontageAttack.SelectedKeyName));
					IInterfaceEnemyCommon* Inter = Cast<IInterfaceEnemyCommon>(Enemy);
					if (Montage && Inter)
					{
						//Inter->AIAttack(Montage, FSimpleDelegate::CreateUObject(this, &UBTTaskAttackCommon::OnAttackFinished, &OwnerComponent));
						return EBTNodeResult::InProgress;
					}
				}
			}
			else return EBTNodeResult::Failed;
		else return EBTNodeResult::Failed;
	}else return EBTNodeResult::Failed;
	return EBTNodeResult::Failed;
}

void UBTTaskAttackCommon::OnAttackFinished(UBehaviorTreeComponent* OwnerComp)
{
	FinishLatentTask(*OwnerComp, EBTNodeResult::Succeeded);
}
