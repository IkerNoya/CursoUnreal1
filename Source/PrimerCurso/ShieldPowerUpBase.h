// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpBase.h"
#include "ShieldPowerUpBase.generated.h"

/**
 * 
 */
UCLASS()
class PRIMERCURSO_API AShieldPowerUpBase : public APowerUpBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int Hp=1;
	virtual void ActivatePowerUp(AShip* Player) override;
};
