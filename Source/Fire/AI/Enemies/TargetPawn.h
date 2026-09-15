// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GenericTeamAgentInterface.h"
#include "TargetPawn.generated.h"
class UCapsuleComponent;
class USkeletalMeshComponent;
class UWidgetComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
struct FAIStimulus;
UCLASS()
class FIRE_API ATargetPawn : public APawn, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATargetPawn();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCapsuleComponent* CapsuleCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UWidgetComponent* WidgetHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAIPerceptionComponent* Perception;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAISenseConfig_Sight* SenseConfig;

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 TeamID = 2; //0 - Neutral, 2 - Frendlies, 1- Enemy

	virtual FGenericTeamId GetGenericTeamId() const override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.f;

	virtual float TakeDamage(float DamageCount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
};
