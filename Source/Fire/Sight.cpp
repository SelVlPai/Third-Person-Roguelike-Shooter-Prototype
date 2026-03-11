// Fill out your copyright notice in the Description page of Project Settings.


#include "Sight.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASight::ASight()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshSight"));
	SightMesh->SetupAttachment(SphereCollision);
	MarkerForSight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker"));
	MarkerForSight->SetupAttachment(SightMesh);

	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASight::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("Sight"));
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlapBegin);
	if (SightingTable.DataTable != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, TEXT("Valid"));
		if (FVisualParametersScope* Info = SightingTable.DataTable->FindRow<FVisualParametersScope>(SightingTable.RowName, TEXT("ERR")))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, TEXT("SetMesh"));
			SightVisual = *Info;
			SightMesh->SetStaticMesh(SightVisual.StaticMesh);
			FName SocketName = "Sight";
			if (SightMesh->DoesSocketExist(SocketName))
				MarkerForSight->AttachToComponent(SightMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);
			else
				MarkerForSight->SetStaticMesh(nullptr);

		}
	}
	
}

// Called every frame
void ASight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASight::OnSphereOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OverlapActor, UPrimitiveComponent* OtherActor,
	int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::Printf(TEXT("%s"), *OverlapActor->GetName()));
}

FVisualParametersScope ASight::PickUpItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, TEXT("PickUpSight"));
	Destroy();
	return SightVisual;
}

