// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownShooterGameMode.h"

void ATopDownShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeWidget(StartingWidgetClass);

	static_cast<UGameWidget*>(CurrentWidget)->Load();
	
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

void ATopDownShooterGameMode::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if(CurrentWidget!=nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget=nullptr;
	}
	if(NewWidgetClass!=nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if(CurrentWidget)
		{
			CurrentWidget->AddToViewport(); 	
		}
	}
}

void ATopDownShooterGameMode::AddScore()
{
	Score += ScorePerKill;
	static_cast<UGameWidget*>(CurrentWidget)->SetScore(Score);
}

void ATopDownShooterGameMode::GameOver()
{
	static_cast<UGameWidget*>(CurrentWidget)->OnGameOver(Score);	
}
