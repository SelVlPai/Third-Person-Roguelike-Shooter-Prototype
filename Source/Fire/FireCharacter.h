// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "Logging/LogMacros.h"
#include "WeaponScope.h"
#include "InterfaceMainCharacter.h"
#include "Components/TimelineComponent.h"
#include "FireCharacter.generated.h"
class UInputComponent;
class UStatsCharacter;
class UWidgetComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class ABaseFireWeapon;
class IInterfaceFireWeapon;
class USpringArmComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AFireCharacter : public ACharacter, public IGenericTeamAgentInterface, public IInterfaceMainCharacter
{
	GENERATED_BODY()
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetChangeSight;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//UStatsCharacter* CharacterStats;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UStatsCharacter* StatsPlayer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* TakeMainWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* TakeSecondaryWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* Fire;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* TakeAim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PickUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ChangeSight;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	UPROPERTY()
	AActor* MainWeapon;
	
	UPROPERTY()
	AActor* SecondaryWeapon;
	UPROPERTY()
	AActor* Equiped;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> NavBlokerClass;
	UPROPERTY()
	AActor* NavBlokerRef;
	
	
public:
	AFireCharacter();
	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 TeamID = 1; // 0 - Neutral, 2 - Frendlies, 1 - Enemy

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	void TakeMain();
	void TakeSecondary();
	void FireWeapon();
	void OpenSight();
	UFUNCTION()
	void MontageEnded(UAnimMontage* EndedMontage, bool Interrapted);

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* EquipWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* ChangeWeapon;

	UPROPERTY()
	FVector DefaultPositionCamera = FVector(3.2097f, 4.906876f, -169.999999f);

	UPROPERTY()
	UTimelineComponent* SetAlphaForOpenSight;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* FloatCurve;
	UPROPERTY()
	FOnTimelineFloat UpdateFunctionFloat;

	UFUNCTION()
	void HandleProgress(float Value);
	FVector DefaultLocation;
	FRotator DefaultRotation;
	bool InSight;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UDataTable* TableSightsInfo;
	FString NowTypeSpread = "Idle";
protected:
	// APawn interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual FGenericTeamId GetGenericTeamId() const override;
	

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	virtual bool GetInSight()override { return InSight; };
	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OverlapActor, UPrimitiveComponent* OtherActor,
		int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnSphereOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OverlapActor, UPrimitiveComponent* OtherActor,
		int32 OtherBodyIndex);

	virtual void GetSightEquiped_Implementation(FVisualParametersScope ChangeSightOnOther) override;
	virtual UAnimInstance* GetMesh1PInstanse() override;
	virtual FStatsStruct GetAllStats()override;
	virtual FInfoForWeapon GetMainWeapon() override;
	virtual FInfoForWeapon GetSecondWeapon() override;
	virtual void ActivateBuff(ETypeBuffs Buff, float AddNumberBuff) override;
	virtual void SetOnSeePlayer(bool OnSeePlayer) override;
	virtual float TakeDamage(float DamageCount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Landed(const FHitResult& Hit) override;

private:
	TArray<AActor*> ActorsOverlap;
	TArray <FVisualParametersScope> Sights;
	FVisualParametersScope EquippedSight;
	void PickUpItems();
	void ChangeInEqupedSight();
	bool IsOpenWidget = true;
	void SetAttachWeapon(AActor* PickUpedWeapon);
	bool PlayerWasSeen;
	bool StartJump;
	void StopMove();
	void SetLocationNavBlocked();
	void BeginJump();
	void EndJump();
	void CompleteFire();
	void StartMove();
	TArray<AActor*> OverlapSelf;

	
	
};

