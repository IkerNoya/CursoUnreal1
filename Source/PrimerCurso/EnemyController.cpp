// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "BulletController.h"
#include "TopDownShooterGameMode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"


// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetGenerateOverlapEvents(true);
	Direction= -GetActorForwardVector();

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
	FVector NextPos = GetActorLocation();
	NextPos += (Direction * Speed * DeltaTime);
	SetActorLocation(NextPos);

	if(GetActorLocation().X <= 100.0f)
	{
		Destroy();
	}
	
}

void AEnemyController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(ABulletController::StaticClass()) && !bIsDead)
	{
		DestroyEnemy();
		OtherActor->Destroy();
	}
}
void AEnemyController::DestroyEnemy()
{
	bIsDead=true;
	ATopDownShooterGameMode* GameMode = Cast<ATopDownShooterGameMode>(GetWorld()->GetAuthGameMode());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation(), FRotator::ZeroRotator, FVector(2,2,2), true);
	if(GameMode)
	{
		GameMode->AddScore();
		GameMode->DecidePowerUpSpawn(GetActorLocation());
	}
	Destroy();
}



