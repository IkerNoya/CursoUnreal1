// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpBase.h"

// Sets default values
APowerUpBase::APowerUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SetRootComponent(SphereCollider);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUp Mesh"));
	Mesh->SetupAttachment(SphereCollider);
	
}

// Called when the game starts or when spawned
void APowerUpBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("DaTA: %d"),ShieldHP);
}

// Called every frame
void APowerUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


