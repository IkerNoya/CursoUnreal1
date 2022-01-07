// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpBase.h"
#include "NukePowerUpBase.generated.h"

/**
 * 
 */
UCLASS()
class PRIMERCURSO_API ANukePowerUpBase : public APowerUpBase
{
	GENERATED_BODY()
protected:
	virtual void ActivatePowerUp(AShip* Player) override;
};
