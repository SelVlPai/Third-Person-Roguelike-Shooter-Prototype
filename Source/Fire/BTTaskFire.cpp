// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskFire.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>

UBTTaskFire::UBTTaskFire()
{
	NodeName = TEXT("Fire");
}

EBTNodeResult::Type UBTTaskFire::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	if (AAIController* Controller = OwnerComponent.GetAIOwner())
	{
		Owner = &OwnerComponent;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Check")));
		//ACharacter* TestEnemy = ;
		EnemyCharacter = Controller->GetCharacter();
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		PlayerLocation = Player->GetActorLocation();
		if (EnemyCharacter)
		{
			GetWorld()->GetTimerManager().SetTimer(TShoot, this, &ThisClass::FireGun, 0.3f, false);
			
			return EBTNodeResult::InProgress;
		}
		else return EBTNodeResult::Failed;
		
	}
	else return EBTNodeResult::Failed;
}

void UBTTaskFire::FireGun()
{
	FVector StartTrace = EnemyCharacter->GetMesh()->GetSocketLocation(TEXT("Weapon"));
	FVector ShootDir = (PlayerLocation - EnemyCharacter->GetMesh()->GetSocketLocation(TEXT("Weapon"))).GetSafeNormal();//->GetBoneLocation(TEXT("hand_r"));
	ShootDir = FMath::VRandCone(ShootDir, FMath::DegreesToRadians(FMath::FRandRange(2.f, 5.f)));
	FVector EndTrace = StartTrace + ShootDir * 4000;
	FHitResult Result;
	FCollisionObjectQueryParams OverlapActors;
	OverlapActors.AddObjectTypesToQuery(ECC_Pawn);
	FCollisionQueryParams SelfIgnore;
	SelfIgnore.AddIgnoredActor(EnemyCharacter);
	if (GetWorld()->LineTraceSingleByObjectType(Result, StartTrace, EndTrace, OverlapActors, SelfIgnore))
	{
		if (AActor* HitActor = Result.GetActor())
		{
			/*if (EnemyCharacter->Implements<UInterfaceEnemyRange>())
			{
				UGameplayStatics::ApplyDamage(HitActor, Cast<IInterfaceEnemyRange>(EnemyCharacter)->GetWeaponDamage(),
					EnemyCharacter->GetInstigatorController(), EnemyCharacter, UDamageType::StaticClass());
				GetWorld()->GetTimerManager().ClearTimer(TShoot);
			}*/
		}
		

		/*if (GetWorld())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Yes")));
			//GetWorld()->GetTimerManager().SetTimer(TimerShoot, this, &ThisClass::FireGun, 0.3f, true);
		}*/
		CurrentShots++;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%i"), CurrentShots));
	}
	//Cast<IInterfaceEnemyRange>(EnemyCharacter)->CheckBullet();
	DrawDebugLine(EnemyCharacter->GetWorld(), StartTrace, EndTrace, FColor::Red, false, 1.f, 0, 2.f);
	FinishLatentTask(*Owner, EBTNodeResult::Succeeded);
}
