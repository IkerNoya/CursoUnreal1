// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletController.h"
#include "PowerUpBase.h"
#include "ScatterBlastPowerUpBase.generated.h"

/**
 * 
 */
UCLASS()
class PRIMERCURSO_API AScatterBlastPowerUpBase : public APowerUpBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PowerUps)
	TSubclassOf<ABulletController> Bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PowerUps)
	float ScatterShotFireRate=.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PowerUps)
	bool bActivateSineMovement=false;
	virtual void ActivatePowerUp(AShip* Player) override;

};
