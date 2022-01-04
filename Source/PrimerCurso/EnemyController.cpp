// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "BulletController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyController::OnOverlap);
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!IsDead)
	{
		FVector NextPos = GetActorLocation();
		FVector Direction = -GetActorForwardVector();
		NextPos += (Direction * Speed * DeltaTime);
		SetActorLocation(NextPos);
	}
	if(GetActorLocation().X <= 100.0f)
		Destroy();
	
}

void AEnemyController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(ABulletController::StaticClass()) && !IsDead)
	{
		IsDead=true;
		OtherActor->Destroy();
	}
}

