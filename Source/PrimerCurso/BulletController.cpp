// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletController.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SetRootComponent(SphereCollider);
	
	
}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NextPos = GetActorLocation();
	FVector Direction = GetActorForwardVector();
	if(bActivateSineMovement)
	{
		Direction = FVector(Direction.X, FMath::Sin(GetWorld()->TimeSeconds * SineMagnitude), Direction.Z);
	}
	NextPos += (Direction * Speed * DeltaTime);
	SetActorLocation(NextPos);

	if(GetActorLocation().X >= 3000.0f)
	{
		Destroy();
	}
	
}

