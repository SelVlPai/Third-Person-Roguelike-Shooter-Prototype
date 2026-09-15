// Fill out your copyright notice in the Description page of Project Settings.


#include "Patron.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APatron::APatron()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereCollision == RootComponent;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereCollision);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileComponent->UpdatedComponent = SphereCollision;
	ProjectileComponent->InitialSpeed = 400.f;
	ProjectileComponent->MaxSpeed = ProjectileComponent->InitialSpeed;
	ProjectileComponent->bRotationFollowsVelocity = true;
	ProjectileComponent->bShouldBounce = true;

	InitialLifeSpan = 3.f;
	
}

// Called when the game starts or when spawned
void APatron::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("%s"), StaticMesh->GetName());
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APatron::OnSphereOverlap);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, FString::Printf(TEXT("%f"), ProjectileComponent->GetMaxSpeed()));
}

void APatron::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OtherActor->GetName());
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, OtherActor->GetName());
		UGameplayStatics::ApplyDamage(OtherActor, 20.0f, GetInstigatorController(), this, UDamageType::StaticClass());
		this->Destroy();
	}
}

// Called every frame
void APatron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

