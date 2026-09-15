// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskSetMovementSpeed.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Fire/Interface/InterfaceAnimBP.h"

UBTTaskSetMovementSpeed::UBTTaskSetMovementSpeed()
{
	NodeName = TEXT("SetSpeed");
}

EBTNodeResult::Type UBTTaskSetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	if (AAIController* Controller = OwnerComponent.GetAIOwner())
	{
		if (ACharacter* AIEnemy = Controller->GetCharacter())
		{
			UCharacterMovementComponent* Movement = AIEnemy->GetCharacterMovement();
			Movement->MaxWalkSpeed = SetNewSpeed;
			AIEnemy->bUseControllerRotationYaw = !SetOrient;
			Movement->bOrientRotationToMovement = SetOrient;
			if(UAnimInstance* AnimIns = AIEnemy->GetMesh()->GetAnimInstance())
			if (AnimIns->Implements<UInterfaceAnimBP>())
				IInterfaceAnimBP::Execute_SetOreint(AnimIns, SetOrient);
			return EBTNodeResult::Succeeded;

		}
	}
	return EBTNodeResult::Failed;
}
