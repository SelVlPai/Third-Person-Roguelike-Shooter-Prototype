// Fill out your copyright notice in the Description page of Project Settings.


#include "DropsBuff.h"
#include "InterfaceMainCharacter.h"
#include "PDAInfoAboutBuff.h"
#include "IconBaff.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ADropsBuff::ADropsBuff()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = SphereCollision;
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel3, ECollisionResponse::ECR_Overlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereCollision);

	WidgetIcon = CreateDefaultSubobject<UWidgetComponent>(TEXT("Icon"));
	WidgetIcon->SetupAttachment(SphereCollision);
	WidgetIcon->SetWidgetSpace(EWidgetSpace::World);
	PrimaryActorTick.bCanEverTick = true;

}



void ADropsBuff::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (InfoBaff && InfoBaff->Mesh)
	{
		StaticMesh->SetStaticMesh(InfoBaff->Mesh);
		FBoxSphereBounds Bounds = StaticMesh->CalcBounds(StaticMesh->GetComponentTransform());
		SphereCollision->SetSphereRadius(Bounds.SphereRadius);
		//SphereCollision->SetWorldLocation(Bounds.Origin);

		
	}
}

// Called when the game starts or when spawned
void ADropsBuff::BeginPlay()
{
	Super::BeginPlay();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlapBegin);
	PlayerCamera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	UserWidgetIcon = Cast<UIconBaff>(WidgetIcon->GetUserWidgetObject());
	UserWidgetIcon->SetTexture(InfoBaff->Icon);
	GetWorld()->GetTimerManager().SetTimer(TSetDistance, this, &ThisClass::SetDistance, 0.1, true);
}

void ADropsBuff::SetDistance()
{
	FVector CameraLocation = PlayerCamera->GetCameraLocation();
	FVector WidgetIconLocation = WidgetIcon->GetComponentLocation();
	float DistanceToPlayer = FVector::Distance(CameraLocation, WidgetIconLocation);
	if (DistanceToPlayer < 2000.f)
	{
		FVector ToActor = (GetActorLocation() - CameraLocation).GetSafeNormal();
		float Dot = FVector::DotProduct(PlayerCamera->GetActorForwardVector(), ToActor);
		if (Dot >= 0.65f)
		{
			if (!WidgetIcon->IsVisible())
				WidgetIcon->SetVisibility(true);
			//FVector CameraLocation = PlayerCamera->GetCameraLocation();
			//FVector WidgetLocation = WidgetIcon->GetComponentLocation();
			UserWidgetIcon->SetDistance(FVector::Distance(CameraLocation, WidgetIconLocation));
			WidgetIcon->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(WidgetIconLocation, CameraLocation));
		}
		else
		{
			if (WidgetIcon->IsVisible())
				WidgetIcon->SetVisibility(false);
		}
	}
}

void ADropsBuff::SetInfoForBuff(UPDAInfoAboutBuff* AllInfoForBuff)
{
	InfoBaff = AllInfoForBuff;
}

void ADropsBuff::OnSphereOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OverlapActor, UPrimitiveComponent* OtherActor,
	int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, TEXT("Baff1"));
	if (OverlapActor && OverlapActor->Implements<UInterfaceMainCharacter>())
	{
		Cast<IInterfaceMainCharacter>(OverlapActor)->ActivateBuff(InfoBaff->NameBuff, InfoBaff->AddingCurrentBuff);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, TEXT("Baff2"));
		//Destroy();
	}
}

// Called every frame
void ADropsBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

