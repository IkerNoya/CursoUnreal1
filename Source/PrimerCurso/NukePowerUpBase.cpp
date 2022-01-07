// Fill out your copyright notice in the Description page of Project Settings.


#include "NukePowerUpBase.h"

#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"

void ANukePowerUpBase::ActivatePowerUp(AShip* Player)
{
	Super::ActivatePowerUp(Player);
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyController::StaticClass(), Enemies);
	for (auto Enemy : Enemies)
	{
		if(Enemy)
		{
			AEnemyController* EnemyController = Cast<AEnemyController>(Enemy);
			if(EnemyController && !EnemyController->bIsInmuneToNuke)
			{
				EnemyController->DestroyEnemy();		
			}
		}
		
	}
}
