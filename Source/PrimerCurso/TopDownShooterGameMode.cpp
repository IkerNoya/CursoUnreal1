// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownShooterGameMode.h"

void ATopDownShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeWidget(StartingWidgetClass);

	UGameWidget* Hud = Cast<UGameWidget>(CurrentWidget); // Casteo de Unreal
	if (Hud) // Formas de chequear referencias: IsValid, Ensure (3 tipos)/ Es un MACRO, el de toda la vida, 
	{
		Hud->Load();
	}
	UWorld* World = GetWorld();
	if(World)
	{
		World->GetTimerManager().SetTimer(EnemySpawnTimer, this, &ATopDownShooterGameMode::SpawnEnemy, 1.5f, true, 2);
		World->GetTimerManager().SetTimer(DifficultyTimer, this, &ATopDownShooterGameMode::InreaseDifficulty, TimeToIncreaseDifficulty, true, TimeToIncreaseDifficulty);
	}
}

void ATopDownShooterGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATopDownShooterGameMode::Destroyed()
{
	Super::Destroyed();
	UWorld* World = GetWorld();
	if(World)
	{
		World->GetTimerManager().ClearTimer(EnemySpawnTimer);
		World->GetTimerManager().ClearTimer(DifficultyTimer);
	}
}

void ATopDownShooterGameMode::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ATopDownShooterGameMode::AddScore()
{
	Score += ScorePerKill;
	UGameWidget* Hud = Cast<UGameWidget>(CurrentWidget); // Casteo de Unreal
	if (Hud)
	{
		Hud->SetScore_Implementation(Score);
	}
}

void ATopDownShooterGameMode::GameOver()
{
	ChangeWidget(GameOverWidget);
}

void ATopDownShooterGameMode::SpawnEnemy()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector SpawnPoint = FVector(FMath::RandRange(4000, 5000), FMath::RandRange(-700, 700), 380);
		World->SpawnActor<AEnemyController>(Enemies, SpawnPoint, FRotator::ZeroRotator);
	}
}

void ATopDownShooterGameMode::InreaseDifficulty()
{
	if(TimeToSpawnEnemies>0.5)
	{
		TimeToSpawnEnemies -= 0.5f;
		UWorld* World = GetWorld();
		if(World)
		{
			World->GetTimerManager().SetTimer(EnemySpawnTimer, this,&ATopDownShooterGameMode::SpawnEnemy, TimeToSpawnEnemies, true);
		}
	}
	
}


