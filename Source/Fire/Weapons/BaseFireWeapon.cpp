// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFireWeapon.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Fire/FrameWork/FireCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Fire/Interface/InterfacePlayerController.h"
#include "Fire/FrameWork/MyPlayerController.h"
#include "Fire/AI/Enemies/TargetPawn.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseFireWeapon::ABaseFireWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PhysicsColiision"));
	RootComponent = PhysicsCollision;
	PhysicsCollision->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	PhysicsCollision->SetSimulatePhysics(true);
	PhysicsCollision->SetBoxExtent(FVector(5.f, 45.f, 15.f), false);
	PhysicsCollision->SetLinearDamping(5.f);
	PhysicsCollision->SetMassOverrideInKg(NAME_None, 10.f, true);
	PhysicsCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PhysicsCollision->SetCollisionResponseToChannel(ECC_EngineTraceChannel3, ECollisionResponse::ECR_Overlap);

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	WeaponStaticMesh->SetupAttachment(GetRootComponent());
	WeaponStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponStaticMesh->SetSimulatePhysics(false);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollisionTrigger");
	SphereCollision->SetupAttachment(WeaponStaticMesh);
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);


	/*SightForWeapon = CreateDefaultSubobject<UStaticMeshComponent>("SightStaticMesh");
	SightForWeapon->SetupAttachment(WeaponStaticMesh);

	MarkerMesh = CreateDefaultSubobject<UStaticMeshComponent>("MarkerForSight");
	MarkerMesh->SetupAttachment(SightForWeapon);*/

	Tags.Add(TEXT("FireWeapon"));

}

// Called when the game starts or when spawned
void ABaseFireWeapon::BeginPlay()
{
	Super::BeginPlay();
	//BulletInAutomaton = 0;
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
	if (InfoFromTable.DataTable)
	{
		if (FWeaponScope* Row = InfoFromTable.DataTable->FindRow<FWeaponScope>(InfoFromTable.RowName, TEXT("Er")))
			EquipedScope = *Row;
		/*FWeaponScope* Scope = CoordinateScope->FindRow<FWeaponScope>(TEXT("NewRow"), TEXT("Lookup Scope"));
		if (Scope)
		{
			EquipedScope = *Scope;

			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan,
				FString::Printf(TEXT("X: %f, Y: %f, Z: %f"),
					EquipedScope.LocationForAim.X, EquipedScope.LocationForAim.Y, EquipedScope.LocationForAim.Z));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Row 'NewRow' not found in DataTable!"));
		}*/
	}

	/*
	if (FWeaponScope* Scope = CoordinateScope->FindRow<FWeaponScope>(TEXT("NewRow"), "ERRRRRR"))
		EquipedScope = *Scope;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("f%, f%, f%"),EquipedScope.LocationForAim.X, EquipedScope.LocationForAim.Y, EquipedScope.LocationForAim.Z));
	*/
}

// Called every frame
void ABaseFireWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABaseFireWeapon::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			// Fire
			EnhancedInputComponent->BindAction(RechargeFireAction, ETriggerEvent::Triggered, this, &ABaseFireWeapon::RechargeFire);

	}


}



void ABaseFireWeapon::DamageOnPartsOfBody(FName BoneToShoot)
{
	if (BoneToShoot == "thigh_r" || BoneToShoot == "thigh_l")
	{
		HeadShoot = false;
		GunDamage = *BodyDamage.Find("Legs");
	}
	else if (BoneToShoot == "clavicle_r" || BoneToShoot == "clavicle_l")
	{
		HeadShoot = false;
		GunDamage = *BodyDamage.Find("Hands");
	}
	else if (BoneToShoot == "pelvis")
	{
		HeadShoot = false;
		GunDamage = *BodyDamage.Find("Pelvis");
	}
	else if (BoneToShoot == "neck_01")
	{
		HeadShoot = true;
		GunDamage = *BodyDamage.Find("Head");
	}
}

void ABaseFireWeapon::SetBulletWeaponHUD(FString SetCategory)
{
	MainOrSecondary = SetCategory;
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC && PC->Implements<UInterfacePlayerController>())
	{
		IInterfacePlayerController* inter = Cast<IInterfacePlayerController>(PC);
		if (inter)
		{
			inter->SetBulletInHUD(BulletInAutomaton1, BulletInAutomatonMax, MainOrSecondary);
		}

	}
}

void ABaseFireWeapon::SetVisibilityWeaponHUD()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC && PC->Implements<UInterfacePlayerController>())
	{
		IInterfacePlayerController* inter = Cast<IInterfacePlayerController>(PC);
		if (inter)
		{
			inter->SetVisibilityBullet(ESlateVisibility::Visible, MainOrSecondary);
		}
		//Cast<IInterfacePlayerController>(GetWorld()->GetFirstPlayerController())->SetVisibilityBullet(ESlateVisibility::Visible, MainOrSecondary);
	}
}

void ABaseFireWeapon::StopRechargeHUD(bool SetRecharge)
{
	IsRecharge = SetRecharge;
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC && PC->Implements<UInterfacePlayerController>())
	{
		IInterfacePlayerController* inter = Cast<IInterfacePlayerController>(PC);
		if (inter)
		{
			inter->StopRecharge();
			GetWorld()->GetTimerManager().ClearTimer(Timer);
		}
		//Cast<IInterfacePlayerController>(GetWorld()->GetFirstPlayerController())->SetVisibilityBullet(ESlateVisibility::Visible, MainOrSecondary);
	}
}

FInfoForWeapon ABaseFireWeapon::GetInfoForWeapon() const
{
	FInfoForWeapon Info;
	Info.BulletInAutomaton = BulletInAutomaton1;
	Info.BulletInAutomatonMagazin = BulletInAutomatonMagazin;
	Info.BulletInAutomatonMax = BulletInAutomatonMax;
	Info.ClassWeapon = GetClass();
	Info.GunDamage = GunDamage;
	Info.GunShootDistance = GunShootDistance;
	Info.SpreadMax = SpreadMaxPerShoot;
	Info.SpreadPerShoot = SpreadPerShoot;
	Info.SpreadRecovery = SpreadRecovery;
	Info.SpreadWhenMoving = SpreadMove;
	Info.TimeRecharge = TimeRecharge;
	return Info;
}

void ABaseFireWeapon::SetInfoForWeapon(const FInfoForWeapon& SetInfoWeapon)
{
	BulletInAutomaton1 = SetInfoWeapon.BulletInAutomaton;
	BulletInAutomatonMagazin = SetInfoWeapon.BulletInAutomatonMagazin;
	BulletInAutomatonMax = SetInfoWeapon.BulletInAutomatonMax;
	GunDamage = SetInfoWeapon.GunDamage;
	GunShootDistance = SetInfoWeapon.GunShootDistance;
	SpreadMaxPerShoot = SetInfoWeapon.SpreadMax;
	SpreadPerShoot = SetInfoWeapon.SpreadPerShoot;
	SpreadRecovery = SetInfoWeapon.SpreadRecovery;
	SpreadMove = SetInfoWeapon.SpreadWhenMoving;
	TimeRecharge = SetInfoWeapon.TimeRecharge;
	Cast<IInterfacePlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController())->SetBulletInHUD(BulletInAutomaton1,
		BulletInAutomatonMagazin, MainOrSecondary);
}

void ABaseFireWeapon::SetSpread(FString TypeSpread)
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if (TimerManager.IsTimerActive(TRecoverySpreadCurrent))
		TimerManager.ClearTimer(TRecoverySpreadCurrent);

	if (TypeSpread == TEXT("Move"))
		SpreadTotal = SpreadMove;
	else if (TypeSpread == TEXT("Idle"))
	{
		TimerManager.SetTimer(TRecoverySpreadCurrent, this, &ThisClass::RecoverySreadCurrent, 0.02, true);// Функція повернення віддачі
		SpreadTotal = SpreadIdle;
	}
	else if (TypeSpread == TEXT("Jump"))
		SpreadTotal = SpreadAir;
	else if (TypeSpread == TEXT("InSight"))
	{
		SpreadAir /= 2.f;
		SpreadPerShoot /= 3.f;
		SpreadMaxPerShoot /= 3.f;
		SpreadMove /= 2.f;
		SpreadIdle /= 2.f;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, FString::Printf(TEXT("%f"), SpreadTotal));
		if (SpreadTotal != 0)
			SpreadTotal /= 2.f;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, FString::Printf(TEXT("%f"), SpreadTotal));
	}
	else if (TypeSpread == TEXT("OutSight"))
	{
		SpreadAir *= 2.f;
		SpreadPerShoot *= 3.f;
		SpreadMaxPerShoot *= 3.f;
		SpreadMove *= 2.f;
		SpreadIdle *= 2.f;
		if (SpreadTotal != 0)
			SpreadTotal *= 2.f;
	}
	/*if (TypeSpread == TEXT("Idle"))
		Cast<IInterfacePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ScaleAimSight(1);*/
	Cast<IInterfacePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ScaleAimSight(SpreadTotal);
}

void ABaseFireWeapon::ShowHitMarkerHUD(bool ShootInHead)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC && PC->Implements<UInterfacePlayerController>())
	{
		IInterfacePlayerController* inter = Cast<IInterfacePlayerController>(PC);
		if (inter)
		{
			inter->ShowHitMarkerInHUD(ShootInHead);
			//GetWorld()->GetTimerManager().ClearTimer(Timer);
		}
		//Cast<IInterfacePlayerController>(GetWorld()->GetFirstPlayerController())->SetVisibilityBullet(ESlateVisibility::Visible, MainOrSecondary);
	}
}


void ABaseFireWeapon::Fire()
{
	//if (Character != nullptr && Character->GetController() != nullptr)
	//{
	if (BulletInAutomaton1 != 0 && !IsRecharge)
	{

		UWorld* const World = GetWorld();
		if (World != nullptr && FireSound != nullptr)
		{
			IInterfaceMainCharacter* CharacterMetods = Cast<IInterfaceMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			UAnimInstance* AnimInstance = CharacterMetods->GetMesh1PInstanse();;
			if (AnimInstance != nullptr)
			{
				float CurrentTime = World->GetTimeSeconds();
				// секунди поділити на швидкість пострілу
				if (CurrentTime - LastFireTime >= 60.f / SpeedFire)
				{
					if (World->GetTimerManager().IsTimerActive(TRecoverySpreadAccumulated))
						World->GetTimerManager().ClearTimer(TRecoverySpreadAccumulated);
					LastFireTime = CurrentTime;
					AnimInstance->Montage_Play(FireAnimation, 1.f);

					APlayerController* PlayerController = Cast<APlayerController>(World->GetFirstPlayerController());
					FVector CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();

					FHitResult HitResult;
					FCollisionObjectQueryParams OverlapActors;
					OverlapActors.AddObjectTypesToQuery(ECC_Pawn);
					OverlapActors.AddObjectTypesToQuery(ECC_WorldDynamic);
					OverlapActors.AddObjectTypesToQuery(ECC_WorldStatic);
					OverlapActors.AddObjectTypesToQuery(ECC_PhysicsBody);
					OverlapActors.AddObjectTypesToQuery(ECC_GameTraceChannel2);
					//OverlapActors.AddObjectTypesToQuery(ECC_PhysicsBody);
					FCollisionQueryParams SelfIgnore(SCENE_QUERY_STAT(LineTrace), true, GetOwner());
					SelfIgnore.bReturnPhysicalMaterial = false;
					TArray<AActor*> AllEnemies;
					//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPawn::GetComponentByClass() StaticClass(), AllEnemies);
					SelfIgnore.AddIgnoredActor(GetOwner());//UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

					FVector EndTrace;

					FRotator ControlRotation = PlayerController->GetControlRotation();

					EndTrace = CalculateSpreadGun();
					FVector BulletDirection = (EndTrace - CameraLocation).GetSafeNormal();




					SetFireRecoil((BulletDirection.Rotation() - ControlRotation).GetNormalized());
					/*if (CharacterMetods->GetInSight())
					{*/
					/*Start = PlayerController->GetControlRotation();


					RotatorRecoil = Start;
					RotatorRecoil.Yaw += RecoilPatern[CurrentShoot][1];
					RotatorRecoil.Pitch += RecoilPatern[CurrentShoot][0];

					CurrentRecoil = 0;
					AddingToRecoilYaw = (RotatorRecoil.Yaw - ControlRotation.Yaw) / 10;
					AddingToRecoilPitch = (RotatorRecoil.Pitch - ControlRotation.Pitch) / 10;*/
					Recoil /= 10.f;
					//if (!World->GetTimerManager().IsTimerActive(TFireRecoil))
					//	World->GetTimerManager().SetTimer(TFireRecoil, this, &ThisClass::SetFireRecoil, 0.01, true);
					//EndTrace = CameraLocation + (PlayerController->PlayerCameraManager->GetCameraRotation().Vector() * GunShootDistance);
				/*}
				else
				{*/
					CameraLocation += PlayerController->PlayerCameraManager->GetActorForwardVector() * 280.f;
					if (GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, EndTrace, OverlapActors, SelfIgnore))
					{
						//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("If Hit Actor")));
						if (HitResult.GetActor() && GetOwner())// || HitResult.GetComponent() && GetOwner())
						{
							//SelfIgnore.AddIgnoredComponent(HitResult.GetComponent());
							//if (GetWorld()->LineTraceSingleByObjectType(HitResult, CameraLocation, EndTrace, OverlapActors, SelfIgnore))
							//{
							//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Hit")));
							USkeletalMeshComponent* SkeletalMeshEnemy = HitResult.GetActor()->FindComponentByClass<USkeletalMeshComponent>();
							if (SkeletalMeshEnemy)
							{
								//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Magenta, FString::Printf(TEXT("%s"), *HitResult.GetComponent()->GetName()));
								if (HitResult.GetComponent()->IsA(USphereComponent::StaticClass()))
								{
									HeadShoot = true;
									GunDamage = *BodyDamage.Find("Crit");
								}
								else
								{
									FName ParentBone = SkeletalMeshEnemy->GetParentBone(HitResult.BoneName);
									DamageOnPartsOfBody(CalculateBoneHit(SkeletalMeshEnemy, HitResult.BoneName));
									GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Magenta, FString::Printf(TEXT("%s - %s"), *ParentBone.ToString(), *HitResult.BoneName.ToString()));

								}

								ShowHitMarkerHUD(HeadShoot);
								UGameplayStatics::ApplyDamage(HitResult.GetActor(), GunDamage, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
								Cast<IInterfacePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->ShowDamageToEnemy(GunDamage, HeadShoot, HitResult.GetActor());
								//UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), 20.f, (EndTrace - CameraLocation).GetSafeNormal(), HitResult,
									//GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
							//}
							}
						}
					}
					DrawDebugLine(GetWorld(), CameraLocation, EndTrace,
						FColor::Red, false, 3.f, 0, 1.f);
					//Set Spawn Collision Handling Override
					//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("x = %f y = %f z = %f"), patron->GetActorLocation().X, patron->GetActorLocation().Y, patron->GetActorLocation().Z));

					UGameplayStatics::PlaySoundAtLocation(this, FireSound, UGameplayStatics::GetPlayerCharacter(World, 0)->GetActorLocation());

					BulletInAutomaton1 -= 1;
					//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Patron %i"), BulletInAutomaton));

					if (GetWorld()->GetFirstPlayerController()->Implements<UInterfacePlayerController>())
						Cast<IInterfacePlayerController>(GetWorld()->GetFirstPlayerController())->SetBulletInHUD(BulletInAutomaton1, BulletInAutomatonMax, MainOrSecondary);

					if (BulletInAutomaton1 == 0)
						RechargeFire();
					CurrentShoot++;
				}
			}
		}
	}
	//}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("NotValid")));
	}

	// Try and play the sound if specified


	// Try and play a firing animation if specified

}

void ABaseFireWeapon::SetSight(UStaticMesh* Sight, FName SocketAttach)
{
	//if(SightForWeapon->GetStaticMesh())
	SightForWeapon->SetStaticMesh(Sight);
	SightForWeapon->AttachToComponent(WeaponStaticMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketAttach);
	if (SightForWeapon->DoesSocketExist("Marker"))
		MarkerMesh->AttachToComponent(SightForWeapon, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Marker"));
	if (FWeaponScope* Row = CoordinateScope->FindRow<FWeaponScope>(SocketAttach, TEXT("Er")))
		EquipedScope = *Row;
}

FName ABaseFireWeapon::CalculateBoneHit(USkeletalMeshComponent* Mesh, FName BoneHit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("%s"), *BoneHit.ToString()));
	for (FName Bone : BonesHits)
	{
		if (Mesh->BoneIsChildOf(BoneHit, Bone) || BoneHit == Bone)
			return Bone;
	}
	return BoneHit;
}


void ABaseFireWeapon::SetFireRecoil(FRotator AngleShoot)
{
	float Pitch = -FMath::Abs(AngleShoot.Pitch / FMath::GetMappedRangeValueClamped(FVector2D(0.5f, SpreadMaxPerShoot), FVector2D(50, 10), SpreadTotal));//FMath::Clamp(AngleShoot.Pitch, -MaxRecoil, MaxRecoil);
	float Yaw = AngleShoot.Yaw / FMath::GetMappedRangeValueClamped(FVector2D(0.5f, SpreadMaxPerShoot), FVector2D(50, 10), SpreadTotal);//FMath::Clamp(AngleShoot.Yaw, -MaxRecoil, MaxRecoil);
	APawn* PlayerControllerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	//FRotator BaseRotation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation();
	/*if (TimerManager.IsTimerActive(TFireRecoil))
		TimerManager.ClearTimer(TFireRecoil);*/

	GetWorld()->GetTimerManager().SetTimer(TFireRecoil, [this, Pitch, Yaw, PlayerControllerPawn]()
		{
			AddPitch = FMath::FInterpTo(AddPitch, Pitch, 0.02f, 20.f);
			AddYaw = FMath::FInterpTo(AddYaw, Yaw, 0.02f, 20.f);
			PlayerControllerPawn->AddControllerPitchInput(AddPitch);
			PlayerControllerPawn->AddControllerYawInput(AddYaw);
			if (FMath::IsNearlyEqual(AddPitch, Pitch, 0.001f) && FMath::IsNearlyEqual(AddYaw, Yaw, 0.001f))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("%f - %f"), AddPitch, Pitch));
				GetWorld()->GetTimerManager().ClearTimer(TFireRecoil);
				AddPitch = 0;
				AddYaw = 0;
			}

		},
		0.02f, true);
	//float MaxRecoil = 0.5f;

	//PlayerControllerPawn->AddControllerPitchInput(-AddingToRecoilPitch);
	//PlayerControllerPawn->AddControllerYawInput(AddingToRecoilYaw);
	//float RecoilYaw = Recoil / 2;
	//CurrentRecoil++;
	//if (CurrentRecoil == 10)
	//{
	//	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%f -  %f"), Start.Pitch, Start.Yaw));
	//	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("Timer")));
	//	GetWorld()->GetTimerManager().ClearTimer(TFireRecoil);
	//}
}

void ABaseFireWeapon::RunTimerRecoverySpreadAccumulated()
{
	GetWorld()->GetTimerManager().SetTimer(TRecoverySpreadAccumulated, [this]()
		{
			if (SpreadAccumulatedShot > SpreadPerShoot)
				SpreadAccumulatedShot = FMath::FInterpTo(SpreadAccumulatedShot, SpreadPerShoot, GetWorld()->GetDeltaSeconds(), 10.f);
			else
				GetWorld()->GetTimerManager().ClearTimer(TRecoverySpreadAccumulated);
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%f"), SpreadAccumulatedShot));
		},
		0.02f, true);

}

void ABaseFireWeapon::RecoverySreadCurrent()
{
	if (SpreadTotal > SpreadIdle)
		SpreadTotal = FMath::FInterpTo(SpreadTotal, SpreadIdle, GetWorld()->GetDeltaSeconds(), 10.f);
	else
		GetWorld()->GetTimerManager().ClearTimer(TRecoverySpreadCurrent);
}


FVector ABaseFireWeapon::CalculateSpreadGun()
{
	FVector CameraLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FRotator CameraRotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	SpreadAccumulatedShot += SpreadPerShoot;
	float FinalSpread = SpreadTotal + SpreadAccumulatedShot;
	float SpreadToRadians = FMath::DegreesToRadians(FinalSpread);
	FVector EndTrace = CameraLocation + FMath::VRandCone(CameraRotation.Vector(), SpreadToRadians) * GunShootDistance;
	return EndTrace;
}





void ABaseFireWeapon::RechargeFire()
{
	if (BulletInAutomatonMax != 0 && BulletInAutomaton1 != BulletInAutomatonMagazin)
	{
		UAnimInstance* AnimInstance = Cast<IInterfaceMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetMesh1PInstanse();
		//UAnimInstance* AnimInstance = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetMesh()->GetAnimInstance();//Character->GetMesh1P()->GetAnimInstance();
		if (BulletInAutomaton1 == 0)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Reload"));
			AnimInstance->Montage_Play(ReloadEmpty, 3.3f / TimeRechargeEmpty);
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::RechargeAfterTimer, TimeRechargeEmpty, false);
			Cast<IInterfacePlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController())->RechargeShow(TimeRechargeEmpty);
		}
		else
		{
			AnimInstance->Montage_Play(Reload, 2.5f / TimeRecharge);
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ThisClass::RechargeAfterTimer, TimeRecharge, false);
			Cast<IInterfacePlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetController())->RechargeShow(TimeRecharge);
		}
		IsRecharge = true;

	}
}

FWeaponScope ABaseFireWeapon::GetInfoAboutScope()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("ActivatedInterface"));

	return EquipedScope;
}

void ABaseFireWeapon::ActivateFire()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("ActivatedInterface"));
	Fire();
}

uint8 ABaseFireWeapon::GetBullet()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("ActivatedInterface"));

	return BulletInAutomaton1;
}

void ABaseFireWeapon::SetSightParametrs(UStaticMesh* SetMesh, FName SocketName)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("ActivatedInterface"));

	SetSight(SetMesh, SocketName);
}






void ABaseFireWeapon::RechargeAfterTimer()
{
	IsRecharge = false;
	uint8 HowManyNeedBullet = (BulletInAutomatonMagazin - BulletInAutomaton1);
	uint8 BulletRemained = BulletInAutomatonMax - HowManyNeedBullet;
	if (BulletRemained >= 0 && BulletRemained <= BulletInAutomatonMax)
	{
		BulletInAutomaton1 += HowManyNeedBullet;
		BulletInAutomatonMax = BulletRemained;
	}
	else
	{
		BulletInAutomaton1 += BulletInAutomatonMax;
		BulletInAutomatonMax = 0;
	}
	CurrentShoot = 0;
	Cast<IInterfacePlayerController>(GetWorld()->GetFirstPlayerController())->SetBulletInHUD(BulletInAutomaton1, BulletInAutomatonMax, MainOrSecondary);
	//SetBulletWeaponHUD();
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, FString::Printf(TEXT("Now %i  Remained %i"), BulletInAutomaton1, BulletInAutomatonMax)); //FString::Printf(TEXT(""))

}


void ABaseFireWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ensure we have a character owner
	/*if (Character != nullptr)
	{
		// remove the input mapping context from the Player Controller
		if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(FireMappingContext);

			}
		}
	}
	*/
	// maintain the EndPlay call chain
	Super::EndPlay(EndPlayReason);
}



