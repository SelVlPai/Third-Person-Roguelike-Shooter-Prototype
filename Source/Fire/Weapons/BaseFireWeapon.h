// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fire/Interface/InterfaceFireWeapon.h"
#include "Fire/Data/WeaponScope.h"
#include "BaseFireWeapon.generated.h"

class AFireCharacter;
class USphereComponent;
class UBoxComponent;

	UCLASS(Abstract)
	class FIRE_API ABaseFireWeapon : public AActor, public IInterfaceFireWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseFireWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* Reload;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* ReloadEmpty;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	UStaticMeshComponent* WeaponStaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	UStaticMeshComponent* SightForWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	UStaticMeshComponent* MarkerMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	USphereComponent* SphereCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	UBoxComponent* PhysicsCollision;
	///** MappingContext */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RechargeFireAction;

	/** Make the weapon Fire a Projectile */
	

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void RechargeFire()override;

	virtual FWeaponScope GetInfoAboutScope() override;
	virtual void ActivateFire()override;
	//virtual void RechargeFireWeapon()override;
	virtual uint8 GetBullet()override;
	virtual void SetSightParametrs(UStaticMesh* SetMesh, FName SocketName) override;
	virtual void SetBulletWeaponHUD(FString SetCategory)override;
	virtual void SetVisibilityWeaponHUD() override;
	virtual void StopRechargeHUD(bool SetRecharge)override;
	virtual uint8 const GetBulletInAutomation() override { return BulletInAutomaton1; };
	virtual FInfoForWeapon GetInfoForWeapon() const override;
	virtual void SetInfoForWeapon(const FInfoForWeapon& SetInfoWeapon) override;
	virtual void SetSpread(FString TypeSpread) override;
	virtual void RunTimerRecoverySpreadAccumulated() override;

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION()
	void RechargeAfterTimer();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TimeRecharge;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TimeRechargeEmpty;

	FTimerHandle Timer;
	FTimerHandle TFireRecoil;
	FTimerHandle TRecoverySpreadCurrent;
	FTimerHandle TRecoverySpreadAccumulated;

	FRotator RotatorRecoil;

private:
	/** The Character holding this weapon*/
	//AFireCharacter* Character;
	UPROPERTY()
	bool IsRecharge;
	UPROPERTY()
	float ElapsedTimerRecoveryPreased = 0;
	float SpreadIdle = 1;
	//UFUNCTION()
	//void MontageEnded(UAnimMontage* EndedMontage, bool Interrapted);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpreadMove = 5.f; // Розброс при ходьбі
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpreadMaxPerShoot = 7.f; // Максимальний розброс
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpreadPerShoot = 4.f; // Розброс коли стреляєш
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpreadRecovery = 1.f; // Швидкість повернення розбросу до 0
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpreadAir = 6.f; // Розброс при прижкові
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Recoil = 1.f; // Розброс при прижкові

	float SpreadTotal = 0.f; // Весь розкид в сумі
	float SpreadAccumulatedShot = 0.f; // Тільки при стрельбі в сумі
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GunShootDistance = 4000.f;
	UPROPERTY(BlueprintReadOnly)
	float LastFireTime = 0;
	
	float AddPitch;
	float AddYaw;

	UFUNCTION()
	FVector CalculateSpreadGun();
	UFUNCTION()
	void SetFireRecoil(FRotator AngleShoot);
	void RecoverySreadCurrent();
	void RecoverySpreadAccumulatedShot();


	UPROPERTY()
	uint8 BulletInAutomaton1 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 BulletInAutomatonMagazin = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 BulletInAutomatonMax = 15;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpeedFire = 600.f;

	float AddingToRecoilYaw;
	float AddingToRecoilPitch;
	FRotator Start;
	
	TArray<FVector2D> RecoilPatern =
	{
		{0.8f, 0.f},
		{0.8f, 0.2f},
		{0.8f, 0.3f},
		{0.8f, 0.1f},
		{0.8f, -0.2f},
		{0.8f, -0.4f},
		{0.8f, -0.7f},
		{0.8f, -0.9f},
		{0.8f, -0.4f},
		{0.8f, 0.1f},
		{0.8f, 0.7f},
		{0.8f, 1.4f},
		{0.8f, 1.f},
		{0.7f, 0.5f},
		{0.8f, -0.2f},
		{0.8f, -0.4f},
		{0.8f, -0.7f},
		{0.8f, -0.9f},
		{0.8f, -1.4f},
		{0.8f, -1.9f},
		{0.8f, -0.9f},
		{0.8f, 0.2f},
		{0.8f, 0.3f},
		{0.8f, 0.1f},
		{0.8f, -0.2f},
		{0.8f, -0.4f},
		{0.8f, -0.7f},
		{0.8f, -0.9f},
		{0.8f, -0.4f},
		{0.8f, 0.1f},
		{0.8f, 0.7f}
	};
	uint8 CurrentShoot;
	uint8 CurrentRecoil;
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;
	UFUNCTION()
	FName CalculateBoneHit(USkeletalMeshComponent* Mesh, FName BoneHit);
	UPROPERTY()
	float GunDamage;
	UPROPERTY()
	TArray<FName> BonesHits =
	{
		"thigh_r",
		"thigh_l",
		"neck_01",
		"clavicle_r",
		"clavicle_l",
		"pelvis"
	};
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, float> BodyDamage = 
	{
		{"Legs", 0},
		{"Hands", 0},
		{"Pelvis", 0},
		{"Head", 0},
		{"Crit", 0}
	};
	UFUNCTION()
	void DamageOnPartsOfBody(FName BoneToShoot);
	bool HeadShoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CoordinateScope;
	UPROPERTY(BlueprintReadWrite)
	FWeaponScope EquipedScope;
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle InfoFromTable;

public:
	UPROPERTY()
	FString MainOrSecondary;

	

	uint8 const GetBulletInAutomationMax() const { return BulletInAutomatonMax; };
	
	FString const GetMainOrSecondary() const { return MainOrSecondary; };
	virtual bool const GetIsRecharge() override { return IsRecharge; };
	FWeaponScope const GetEquipedScope() const { return EquipedScope; };

	void SetIsRecharge(bool IsRechargeSet) { IsRecharge = IsRechargeSet; };

	//UFUNCTION()
	
	void ShowHitMarkerHUD(bool ShootInHead);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();
	UFUNCTION()
	void SetSight(UStaticMesh* Sight, FName SocketAttach);
	
};

