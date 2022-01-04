// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetGenerateOverlapEvents(true);
	SetRootComponent(BoxCollider);

}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NextPos = GetActorLocation();
	FVector Direction = -GetActorForwardVector();
	NextPos += Direction * Speed * DeltaTime;
	if(GetActorLocation().X <= 100.0f)
		Destroy();
	
}

