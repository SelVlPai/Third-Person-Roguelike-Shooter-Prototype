// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "Fire/UI/CW_HealthEnemy.h"


// Sets default values
ATargetPawn::ATargetPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//CapsuleCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	CapsuleCollision == RootComponent;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleCollision);

	WidgetHealth = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetHealth->SetupAttachment(CapsuleCollision);
	WidgetHealth->SetWidgetSpace(EWidgetSpace::Screen);

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SenseConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfig"));
	SenseConfig->SightRadius = 1200.f;
	SenseConfig->LoseSightRadius = 1600.f;
	SenseConfig->PeripheralVisionAngleDegrees = 180.f;
	SenseConfig->DetectionByAffiliation.bDetectEnemies = true;
	Perception->ConfigureSense(*SenseConfig);
	Perception->SetDominantSense(SenseConfig->GetSenseImplementation());

}

// Called when the game starts or when spawned
void ATargetPawn::BeginPlay()
{
	Super::BeginPlay();
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ATargetPawn::OnPerception);
	
}



FGenericTeamId ATargetPawn::GetGenericTeamId() const
{
	return FGenericTeamId(TeamID);
}

// Called every frame
void ATargetPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATargetPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float ATargetPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("TakeDamage"));
	Health -= DamageAmount;
	if (Health <= 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Damage = %f - Health = %f  DESTROY"), DamageAmount, Health));
		this->Destroy();
	}
	else
	{
		if (WidgetHealth && WidgetHealth->GetUserWidgetObject())
		{
			if (UCW_HealthEnemy* MainWidget = Cast<UCW_HealthEnemy>(WidgetHealth->GetUserWidgetObject()))
			{
				MainWidget->UpdateHealth(Health, MaxHealth);
				if (DamageCauser != nullptr)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Damage = %f - Health = %f - Name = %s"), DamageAmount, Health, *DamageCauser->GetName()));
				}
			}
		}
		
		
	};
	return DamageAmount;
}



void ATargetPawn::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor) return;
	
	if (Stimulus.WasSuccessfullySensed())
	{
		IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(Actor);
		if (TeamAgent && TeamAgent->GetGenericTeamId().GetId() == 1)
		{
			WidgetHealth->SetVisibility(true);
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("yes %s"), *Actor->GetName() ));
		}
	}
	else
	{
		WidgetHealth->SetVisibility(false);
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Lose %s"), *Actor->GetName()));
	}

}
