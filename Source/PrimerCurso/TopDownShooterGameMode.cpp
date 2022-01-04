// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownShooterGameMode.h"

void ATopDownShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATopDownShooterGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GameTimer += DeltaSeconds;
	EnemyTimer -= DeltaSeconds;

	if(EnemyTimer<=0.0f)
	{
		float DificultyPercentage = FMath::Min(GameTimer/TimeToMaxDifficulty, 1.0f);
		EnemyTimer = MaxTimeToSpawn - (MaxTimeToSpawn -  MinimumTimeToSpawn) * DificultyPercentage;
		UWorld* World = GetWorld();
		if(World)
		{
			FVector SpawnPoint = FVector(FMath::RandRange(4000, 5000), FMath::RandRange(-700, 700), 380);
			World->SpawnActor<AEnemyController>(Enemies, SpawnPoint, FRotator::ZeroRotator);
		}
	}

}
