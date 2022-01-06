// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "GameWidget.h"
#include "../../Plugins/Developer/RiderLink/Source/RD/src/rd_core_cpp/src/main/types/Void.h"
#include "GameFramework/GameMode.h"
#include "TopDownShooterGameMode.generated.h"
class APowerUpBase;

/**
 * 
 */
UCLASS()
class PRIMERCURSO_API ATopDownShooterGameMode : public AGameMode
{
	GENERATED_BODY()

	float MinimumTimeToSpawn = .4f;
	float MaxTimeToSpawn = 2.5f;
	float TimeToMaxDifficulty = 60.0f;

	FTimerHandle EnemySpawnTimer;
	FTimerHandle DifficultyTimer;
public:
	UPROPERTY(EditAnywhere, Category = Spawn)
	TSubclassOf<AEnemyController>Enemies;

	float EnemyTimer;
	float GameTimer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	int Score;
	
protected:
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget>StartingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget>GameOverWidget;
	UPROPERTY()
	UUserWidget* CurrentWidget;
	UPROPERTY(EditAnywhere, Category=Gameplay)
	float TimeToSpawnEnemies = 2;
	UPROPERTY(EditAnywhere, Category=Gameplay)
	float TimeToIncreaseDifficulty=30;
	UPROPERTY(EditAnywhere, Category = Gameplay)
	TArray<TSubclassOf<APowerUpBase>> PowerUps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	int ScorePerKill = 100;
	

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, Category = UI)
	void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	
	void AddScore();
	void GameOver();
	void SpawnEnemy();
	void IncreaseDifficulty();
	void DecidePowerUpSpawn(FVector Location);
}; 
