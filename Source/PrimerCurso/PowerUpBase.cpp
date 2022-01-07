// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpBase.h"

#include "Kismet/GameplayStatics.h"
#include "Ship.h"

// Sets default values
APowerUpBase::APowerUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SetRootComponent(SphereCollider);
	SphereCollider->SetGenerateOverlapEvents(true);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUp Mesh"));
	Mesh->SetupAttachment(SphereCollider);

}

// Called when the game starts or when spawned
void APowerUpBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerToDestroy, this, &APowerUpBase::DestroyPowerUp, TimeToDestroy, false);
	
}

void APowerUpBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &APowerUpBase::OnOverlap);

}

void APowerUpBase::ActivatePowerUp(AShip* Player)
{
}

void APowerUpBase::BeginDestroy()
{
	UWorld* World = GetWorld();
	if(World)
	{
		World->GetTimerManager().ClearTimer(TimerToDestroy);
	}
	Super::BeginDestroy();
	
}

// Called every frame
void APowerUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUpBase::DestroyPowerUp()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerToDestroy);
	Destroy();
}

void APowerUpBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(OtherActor->IsA(AShip::StaticClass()))
	{

		AShip* Player = Cast<AShip>(OtherActor);
		if(Player)
		{
			ActivatePowerUp(Player);
		}
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickUpParticle, GetActorLocation(), FRotator::ZeroRotator, FVector::OneVector, true);
		Destroy();
	}
}



