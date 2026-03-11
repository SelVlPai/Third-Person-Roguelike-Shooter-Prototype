// Copyright Epic Games, Inc. All Rights Reserved.

#include "FireCharacter.h"
#include "EnemyBase.h"
#include "MainGameMode.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "StatsCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "BaseFireWeapon.h"
#include "InterfacePlayerController.h"
#include "InterfaceGameMode.h"
#include "InterfaceFireWeapon.h"
#include "InterfaceWChooseSights.h"
#include "SaveGamePlayerInfo.h"
#include "MainGameInstance.h"
#include "PickUpDrop.h"
#include "Components/Widget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/SpringArmComponent.h>


			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Attac")));

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AFireCharacter

AFireCharacter::AFireCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->TargetArmLength = 400.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(CameraBoom);
	//FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(GetCapsuleComponent());
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	//CharacterStats = CreateDefaultSubobject<UStatsCharacter>(TEXT("CharacterStats"));
	//CharacterStats->SetFrontHealth(100.f);	
	StatsPlayer = CreateDefaultSubobject<UStatsCharacter>(TEXT("Stats"));
}

void AFireCharacter::BeginPlay()
{
	Super::BeginPlay();
	//EquippedSight.ScopeName = ENameScopes::None;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereOverlapEnd);
	//LandedDelegate.AddDynamic(this, &ThisClass::EndJump);
	WidgetChangeSight = FindComponentByClass<UWidgetComponent>();
	/*if (Mesh1P->DoesSocketExist(FName("ShowAllSights")))
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Not")));

	else
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Yes")));
		*/
	if (FloatCurve)
	{
		SetAlphaForOpenSight = NewObject<UTimelineComponent>(this, FName("MyTimeline"));
		SetAlphaForOpenSight->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(SetAlphaForOpenSight);
		SetAlphaForOpenSight->RegisterComponent();

		UpdateFunctionFloat.BindUFunction(this, FName("HandleProgress"));

		SetAlphaForOpenSight->AddInterpFloat(FloatCurve, UpdateFunctionFloat);
		SetAlphaForOpenSight->SetLooping(false);
		SetAlphaForOpenSight->SetIgnoreTimeDilation(true);

		//SetAlphaForOpenSight->PlayFromStart();
	}
	DefaultLocation = Mesh1P->GetRelativeLocation();
	DefaultRotation = Mesh1P->GetRelativeRotation();

	NavBlokerRef = GetWorld()->SpawnActor<AActor>(NavBlokerClass, GetActorLocation(), FRotator::ZeroRotator);
	WidgetChangeSight->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Collapsed);
}


void AFireCharacter::OnSphereOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OverlapActor, UPrimitiveComponent* OtherActor,
	int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	ActorsOverlap.Add(OverlapActor);

	//if (OverlapActor->Implements<UPickUpDrop>()) 
	//{
	//	Cast<IPickUpDrop>(OverlapActor)->PickUpItem();
	//}
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%i"), Sights.Num()));
}
void AFireCharacter::OnSphereOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OverlapActor, UPrimitiveComponent* OtherActor, int32 OtherBodyIndex)
{
	ActorsOverlap.Remove(OverlapActor);

	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%i"), ActorsOverlap.Num()));
}

void AFireCharacter::GetSightEquiped_Implementation(FVisualParametersScope ChangeSightOnOther)
{
	if (Equiped)
	{
		FString EnumToString = StaticEnum<ENameScopes>()->GetNameStringByValue((int64)ChangeSightOnOther.ScopeName);
		FName NameSight(*EnumToString);
		if (Equiped->Implements<UInterfaceFireWeapon>())
			Cast<IInterfaceFireWeapon>(Equiped)->SetSightParametrs(ChangeSightOnOther.StaticMesh, NameSight);
		//Equiped->SetSight(ChangeSightOnOther.StaticMesh, NameSight);
		Sights.Remove(ChangeSightOnOther);
		//EquippedSight = ChangeSightOnOther;
		if (EquippedSight.ScopeName != ENameScopes::None)
		{
			Sights.Add(EquippedSight);
		}
	}
	WidgetChangeSight->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Collapsed);
	IsOpenWidget = !IsOpenWidget;
	EquippedSight = ChangeSightOnOther;
	//	Equiped
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Interface"));
}

UAnimInstance* AFireCharacter::GetMesh1PInstanse()
{
	return GetMesh1P()->GetAnimInstance();
}

FStatsStruct AFireCharacter::GetAllStats()
{
	FStatsStruct Info;
	Info.BackHealth = StatsPlayer->GetBackHealth();
	Info.FrontHealth = StatsPlayer->GetFrontHealth();
	Info.MaxHealth = StatsPlayer->GetMaxHealth();
	Info.MaxCurrentArmor = StatsPlayer->GetMaxCurrentArmor();
	Info.MaxPlateArmor = StatsPlayer->GetMaxPartsArmor();
	Info.ArmorNow = StatsPlayer->GetArmor();
	return Info;
}

FInfoForWeapon AFireCharacter::GetMainWeapon()
{
	FInfoForWeapon Main;
	if (MainWeapon)
	{
		Main = Cast<IInterfaceFireWeapon>(MainWeapon)->GetInfoForWeapon();
		return Main;
	}
	return FInfoForWeapon{};
}

FInfoForWeapon AFireCharacter::GetSecondWeapon()
{
	FInfoForWeapon Second;
	if (SecondaryWeapon)
	{
		Second = Cast<IInterfaceFireWeapon>(SecondaryWeapon)->GetInfoForWeapon();
		return Second;
	}
	return FInfoForWeapon{};
}

void AFireCharacter::ActivateBuff(ETypeBuffs Buff, float AddNumberBuff)
{
	switch (Buff)
	{
	case ETypeBuffs::Health:
		StatsPlayer->BuffRecoveryHealth(AddNumberBuff);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Health"));
		break;
	case ETypeBuffs::Armor:
		StatsPlayer->BuffRecoveryArmor(AddNumberBuff);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Armor"));
		break;
	case ETypeBuffs::Speed:
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Speed"));
		break;
	default:
		break;
	}
}



float AFireCharacter::TakeDamage(float DamageCount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	StatsPlayer->InflictDamage(DamageCount);
	if (StatsPlayer->GetFrontHealth() <= 0 && UGameplayStatics::DoesSaveGameExist(TEXT("SaveWaveEnd"), 0))
	{
		Cast<IInterfacePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->CreateLoadingWidget();
		FTimerDelegate TimerDel;
		TimerDel.BindLambda([this]()
			{
				//Cast<IInterfacePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->CreateLoadingWidget();
				TArray<AActor*> AllEnemiesOnMap;
				//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), AllEnemiesOnMap);
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), AllEnemiesOnMap);
				const FSavePlayerInfo* Info = GetGameInstance<UMainGameInstance>()->GetSaveWave();
				Cast<IInterfaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->LaunchSavedWave(Info->SavedCurrentWave);
				for (AActor* Actor : AllEnemiesOnMap)
				{
					if (!IsValid(Actor))
						continue;
					if (Actor->IsPendingKillPending())
						continue;
					Actor->Destroy();
				}
				//if (!Info) return 0;
				SetActorTransform(Info->PositionPlayer);
				StatsPlayer->SetAttributesPlayer(Info->StatsPlayer);
				if (MainWeapon)
				{
					Cast<IInterfaceFireWeapon>(MainWeapon)->SetInfoForWeapon(Info->MainWeapon);
				}
				else
					//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Null")));
				if (SecondaryWeapon)
					Cast<IInterfaceFireWeapon>(SecondaryWeapon)->SetInfoForWeapon(Info->SecondWeapon);
			});
		GetWorldTimerManager().SetTimerForNextTick(TimerDel);
		//TArray<AActor*> AllEnemiesOnMap;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), AllEnemiesOnMap);
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), AllEnemiesOnMap);
		//const FSavePlayerInfo* Info = GetGameInstance<UMainGameInstance>()->GetSaveWave();
		//Cast<IInterfaceGameMode>( UGameplayStatics::GetGameMode(GetWorld()) )->LaunchSavedWave(Info->SavedCurrentWave);
		//for (AActor* Actor : AllEnemiesOnMap)
		//{
		//	if (!IsValid(Actor))
		//		continue;
		//	if (Actor->IsPendingKillPending())
		//		continue;
		//	Actor->Destroy();
		//}
		//if (!Info) return 0;
		//SetActorTransform(Info->PositionPlayer);
		//StatsPlayer->SetAttributesPlayer(Info->StatsPlayer);
		//if (MainWeapon)
		//{
		//	Cast<IInterfaceFireWeapon>(MainWeapon)->SetInfoForWeapon(Info->MainWeapon);
		//	if(Info->MainWeapon.ClassWeapon)
		//		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Valid")));
		//	else
		//	{
		//		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("NotValid")));

		//	}
		//}
		//else
		//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Null")));
		//if (SecondaryWeapon)
		//	Cast<IInterfaceFireWeapon>(SecondaryWeapon)->SetInfoForWeapon(Info->SecondWeapon);
		//USaveGamePlayerInfo* Loaded = Cast<USaveGamePlayerInfo>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveWaveEnd"), 0));
		//FSavePlayerInfo LoadedInfoPlayer = Loaded->GetAllInfo();
		//SetActorTransform(LoadedInfoPlayer.PositionPlayer);
	};
	return DamageCount;
}




//////////////////////////////////////////////////////////////////////////// Input

		//TimeLine//

void AFireCharacter::HandleProgress(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Sight")));
	FWeaponScope InfoForScope = Cast<IInterfaceFireWeapon>(Equiped)->GetInfoAboutScope();
	if (InSight)
	{
		FirstPersonCameraComponent->SetFieldOfView(FMath::Lerp(100.f, InfoForScope.AimFOV, Value));
		CameraBoom->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 55.154165f), InfoForScope.LocationForAim, Value));
		//Mesh1P->SetRelativeRotation(FQuat::Slerp(DefaultRotation.Quaternion(), InfoForScope.RotationForAim.Quaternion(), Value));
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMax = 30;
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMin = -30;
	}
	else
	{
		FirstPersonCameraComponent->SetFieldOfView(FMath::Lerp(InfoForScope.AimFOV, 100.f, Value));
		CameraBoom->SetRelativeLocation(FMath::Lerp(InfoForScope.LocationForAim, FVector(0, 0, 55.154165f), Value));
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMax = 70;
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->ViewPitchMin = -70;
		//Mesh1P->SetRelativeRotation(FQuat::Slerp(InfoForScope.RotationForAim.Quaternion(), DefaultRotation.Quaternion(), Value));
	}
}

void AFireCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AFireCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AFireCharacter::BeginJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFireCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AFireCharacter::StartMove);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AFireCharacter::StopMove);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFireCharacter::Look);
		EnhancedInputComponent->BindAction(TakeMainWeapon, ETriggerEvent::Triggered, this, &AFireCharacter::TakeMain);
		EnhancedInputComponent->BindAction(TakeSecondaryWeapon, ETriggerEvent::Triggered, this, &AFireCharacter::TakeSecondary);
		EnhancedInputComponent->BindAction(Fire, ETriggerEvent::Triggered, this, &AFireCharacter::FireWeapon);
		EnhancedInputComponent->BindAction(Fire, ETriggerEvent::Completed, this, &AFireCharacter::CompleteFire);
		EnhancedInputComponent->BindAction(TakeAim, ETriggerEvent::Triggered, this, &AFireCharacter::OpenSight);
		EnhancedInputComponent->BindAction(PickUp, ETriggerEvent::Triggered, this, &AFireCharacter::PickUpItems);
		EnhancedInputComponent->BindAction(ChangeSight, ETriggerEvent::Triggered, this, &AFireCharacter::ChangeInEqupedSight);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AFireCharacter::PickUpItems()
{
	for (AActor* Actor : ActorsOverlap)
	{
		if (Actor && Actor->Implements<UPickUpDrop>())
		{

			if (Actor->ActorHasTag(FName("Sight")))
			{
				Sights.Add(Cast<IPickUpDrop>(Actor)->PickUpItem());
				ActorsOverlap.Remove(Actor);
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Attac")));
				break;
			}
		}
		else if (Actor->ActorHasTag(TEXT("FireWeapon")))
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Attac")));
			//Actor->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "GripPoint");
			//MainWeapon = Actor;
			//Equiped = Actor;
			SetAttachWeapon(Actor);
			ActorsOverlap.Remove(Actor);
			//Cast<IInterfaceFireWeapon>(Actor)->RechargeFire();

		}


	}
}

void AFireCharacter::ChangeInEqupedSight()
{
	IsOpenWidget = !IsOpenWidget;
	UUserWidget* WidgetReferences = WidgetChangeSight->GetUserWidgetObject();
	if (!IsOpenWidget)
	{
		if (WidgetReferences)
		{
			//WidgetChangeSight->SetVisibility(true, false);
			//Equiped->GetMainOrSecondary();
			if (WidgetReferences->Implements<UInterfaceWChooseSights>())
			{
				WidgetReferences->SetVisibility(ESlateVisibility::Visible);
				IInterfaceWChooseSights::Execute_ShowChooseSights(WidgetReferences, this, Sights);
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%i"), Sights.Num()));
			}
		}
	}
	else
	{
		if (WidgetReferences)
			WidgetReferences->SetVisibility(ESlateVisibility::Collapsed);
		//WidgetChangeSight->SetVisibility(false, false);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("false"));
	}
}

FGenericTeamId AFireCharacter::GetGenericTeamId() const
{
	return FGenericTeamId(TeamID);
}



void AFireCharacter::SetAttachWeapon(AActor* PickUpedWeapon)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("SetAttach"));
	//ABaseFireWeapon* CloneEquiped = Equiped;
	IInterfaceFireWeapon* IWeapon = Cast<IInterfaceFireWeapon>(PickUpedWeapon);
	PickUpedWeapon->SetOwner(this);
	PickUpedWeapon->FindComponentByClass<USphereComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UBoxComponent* BoxCollision = PickUpedWeapon->FindComponentByClass<UBoxComponent>();
	BoxCollision->SetSimulatePhysics(false);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (!MainWeapon)
	{
		MainWeapon = PickUpedWeapon;
		IWeapon->SetBulletWeaponHUD(FString("Main"));
		IWeapon->SetVisibilityWeaponHUD();
		if (!Equiped)//&& Equiped != MainWeapon)
		{
			Equiped = PickUpedWeapon;
			IWeapon->RechargeFire();
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			PickUpedWeapon->AttachToComponent(GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
			//Weapon->SetActorRelativeLocation(FVector(0.315984, 3.451356, 2.592682));
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("EquipMain"));
		}
		else
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			PickUpedWeapon->AttachToComponent(GetMesh1P(), AttachmentRules, FName(TEXT("SecondaryWeapon")));
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Dont"));
		}

	}
	else if (!SecondaryWeapon)
	{

		SecondaryWeapon = PickUpedWeapon;
		IWeapon->SetBulletWeaponHUD(FString("Secondary"));
		IWeapon->SetVisibilityWeaponHUD();
		if (!Equiped)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("SecondaryEquip"));
			//Equiped->RechargeFire();
			Equiped = PickUpedWeapon;
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			PickUpedWeapon->AttachToComponent(GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
		}
		else
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			PickUpedWeapon->AttachToComponent(GetMesh1P(), AttachmentRules, FName(TEXT("SecondaryWeapon")));
		}
	}
}


void AFireCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator ControlRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);


		//AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		//AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFireCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFireCharacter::TakeMain()
{

	if (Equiped != MainWeapon && MainWeapon)
	{
		UAnimInstance* AnimInstance = GetMesh1P()->GetAnimInstance();
		if (!AnimInstance->Montage_IsPlaying(EquipWeapon) && !AnimInstance->Montage_IsPlaying(ChangeWeapon))
		{
			//Equiped = SecondaryWeapon;
			//FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			//SecondaryWeapon->AttachToComponent(GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
			//MainWeapon->AttachToComponent(GetMesh1P(), AttachmentRules, FName(TEXT("SecondaryWeapon")));
			AnimInstance->Montage_Play(ChangeWeapon, 1.f);
			AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::MontageEnded);

			if (IInterfaceFireWeapon* IWeapon = Cast<IInterfaceFireWeapon>(SecondaryWeapon))
			{
				if (IWeapon->GetIsRecharge())
					IWeapon->StopRechargeHUD(false);
				//SecondaryWeapon->SetIsRecharge(false);
			}

		}

	}
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("TakeMain"));
}

void AFireCharacter::TakeSecondary()
{
	if (Equiped != SecondaryWeapon && SecondaryWeapon)
	{
		UAnimInstance* AnimInstance = GetMesh1P()->GetAnimInstance();
		if (!AnimInstance->Montage_IsPlaying(EquipWeapon))
		{
			AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::MontageEnded);
			AnimInstance->Montage_Play(ChangeWeapon, 1.f);

			if (IInterfaceFireWeapon* IWeapon = Cast<IInterfaceFireWeapon>(MainWeapon))
			{
				if (IWeapon->GetIsRecharge())
					IWeapon->StopRechargeHUD(false);
				//MainWeapon->SetIsRecharge(false);
			}

		}
	}

}

void AFireCharacter::MontageEnded(UAnimMontage* EndedMontage, bool Interrapted)
{

	if (EndedMontage == EquipWeapon)
	{
		if (IInterfaceFireWeapon* IWeapon = Cast<IInterfaceFireWeapon>(Equiped))
			if (IWeapon->GetBulletInAutomation() == 0)
				IWeapon->RechargeFire();
		GetMesh1P()->GetAnimInstance()->OnMontageEnded.RemoveDynamic(this, &ThisClass::MontageEnded);
	}
	else if (EndedMontage == ChangeWeapon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("MontageEWnded"));
		GetMesh1P()->GetAnimInstance()->Montage_Play(EquipWeapon, 1.f);
		FName NameForMain;
		FName NameForSecondary;
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		if (InSight)
		{
			IInterfaceFireWeapon* IWeapon = Cast<IInterfaceFireWeapon>(Equiped);
			if (IWeapon)
			{
				IWeapon->SetSpread("OutSight");
				SetAlphaForOpenSight->SetPlayRate(1 / IWeapon->GetInfoAboutScope().AimTime);
				SetAlphaForOpenSight->PlayFromStart();
				InSight = !InSight;
			}
		}
		if (Equiped == MainWeapon)
		{
			NameForMain = "SecondaryWeapon";
			NameForSecondary = "GripPoint";

			Equiped = SecondaryWeapon;
		}
		else
		{
			NameForMain = "GripPoint";
			NameForSecondary = "SecondaryWeapon";
			Equiped = MainWeapon;
		}
		//FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(NowTypeSpread);
		MainWeapon->AttachToComponent(GetMesh1P(), AttachmentRules, NameForMain);
		SecondaryWeapon->AttachToComponent(GetMesh1P(), AttachmentRules, NameForSecondary);



	}

}

void AFireCharacter::FireWeapon()
{
	if (!GetMesh1P()->GetAnimInstance()->Montage_IsPlaying(EquipWeapon) && !GetMesh1P()->GetAnimInstance()->Montage_IsPlaying(ChangeWeapon))

		if (IInterfaceFireWeapon* IWeapon = Cast<IInterfaceFireWeapon>(Equiped))
			IWeapon->ActivateFire();//->Fire();
}

void AFireCharacter::CompleteFire()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Complete"));
	if (Equiped)
		Cast<IInterfaceFireWeapon>(Equiped)->RunTimerRecoverySpreadAccumulated();
}



void AFireCharacter::OpenSight()
{
	//StatsPlayer->RecoveryPlate(2);
	//StatsPlayer->AddNewPlate();
	//StatsPlayer->SetArmor(76.f, true);//SetFrontHealth(CharacterStats->GetFrontHealth() - 15.f);
	if (Equiped)
	{
		if (IInterfaceFireWeapon* IWeapon = Cast<IInterfaceFireWeapon>(Equiped))
			SetAlphaForOpenSight->SetPlayRate(1 / IWeapon->GetInfoAboutScope().AimTime);
		if (InSight)
		{
			Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("OutSight"));
			SetAlphaForOpenSight->PlayFromStart();

		}
		else
		{
			Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("InSight"));
			SetAlphaForOpenSight->PlayFromStart();
			//FirstPersonCameraComponent->SetRelativeLocation

		}
		InSight = !InSight;
	}
}

void AFireCharacter::SetOnSeePlayer(bool OnSeePlayer)
{
	PlayerWasSeen = OnSeePlayer;
	if (PlayerWasSeen)
	{
		float Distance = FVector::Dist(NavBlokerRef->GetActorLocation(), GetActorLocation());
		//NavBlokerRef->GetOverlappingActors(OverlapSelf, ACharacter::StaticClass());
		if (Distance >= 100.f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Spawn"));
			NavBlokerRef->SetActorLocation(GetActorLocation());
		}
		else GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("NotSpawn"));
	}
}

void AFireCharacter::StartMove()
{
	if (Equiped && !StartJump)
	{
		Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("Move"));
		NowTypeSpread = "Move";
	}
	/*else if (Equiped && GetVelocity().Length() < 10.f)
		Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("Idle"));*/
}

void AFireCharacter::StopMove()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("%f"), GetVelocity().Z));
	if (Equiped && !StartJump)
	{
		Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("Idle"));
		NowTypeSpread = "Idle";
	}
}

void AFireCharacter::SetLocationNavBlocked()
{

}

void AFireCharacter::BeginJump()
{
	StartJump = true;
	Jump();
	if (Equiped)
	{
		Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("Jump"));
		NowTypeSpread = "Jump";
	}
}

void AFireCharacter::Landed(const FHitResult& Hit)
{
	StartJump = false;
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("%f , %f"), GetVelocity().Y, GetVelocity().X));
	if (Equiped && FMath::Abs(GetVelocity().X) < 10.f && FMath::Abs(GetVelocity().Y) < 10)
	{
		Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("Idle"));
		NowTypeSpread = "Idle";
	}
	else if (Equiped && FMath::Abs(GetVelocity().X) > 10.f || Equiped && FMath::Abs(GetVelocity().Y) > 10)
	{
		Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("Move"));
		NowTypeSpread = "Move";
	}
}

void AFireCharacter::EndJump()
{
	StopJumping();
	if (Equiped && GetVelocity().Length() < 10.f)
		Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("Idle"));
	else if (Equiped && GetVelocity().Length() > 10.f)
		Cast<IInterfaceFireWeapon>(Equiped)->SetSpread(TEXT("Move"));
}



