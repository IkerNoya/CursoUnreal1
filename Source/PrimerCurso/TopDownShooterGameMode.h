// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "GameWidget.h"
#include "../../Plugins/Developer/RiderLink/Source/RD/src/rd_core_cpp/src/main/types/Void.h"
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
public:
	UPROPERTY(EditAnywhere, Category = Spawn)
	TSubclassOf<class AEnemyController>Enemies;

	float EnemyTimer;
	float GameTimer;
protected:
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget>StartingWidgetClass;
	UPROPERTY()
	UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	int ScorePerKill = 100;
	
	int Score;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = UI)
	void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	
	void AddScore();
	void GameOver();
	
}; 
