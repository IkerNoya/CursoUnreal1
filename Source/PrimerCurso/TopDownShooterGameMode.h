// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "GameFramework/GameMode.h"
#include "TopDownShooterGameMode.generated.h"

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
	
	UPROPERTY(EditAnywhere, Category = Spawn)
	TSubclassOf<class AEnemyController>Enemies;
	float EnemyTimer;
	float GameTimer;
protected:
	int score;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
}; 
