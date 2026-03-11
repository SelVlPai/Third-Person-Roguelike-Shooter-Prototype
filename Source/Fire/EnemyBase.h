// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GenericTeamAgentInterface.h>
#include "EnemyBase.generated.h"
UCLASS()
class FIRE_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

	uint8 TeamID = 2; //0 - Neutral, 2 - Frendlies, 1- Enemy

	FGenericTeamId GetGenericTeamId() const
	{
		return FGenericTeamId(TeamID);
	}

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.f;
	FTimerHandle TFireRange;
	uint8 CurrentShoots;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float WeaponDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "VALUE"))
	float Duraction;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//virtual void FireRange() override;
	//virtual float GetWeaponDamage() override { return WeaponDamage; };
	//virtual void CheckBullet() override;
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
