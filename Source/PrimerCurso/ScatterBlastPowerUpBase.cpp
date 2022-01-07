// Fill out your copyright notice in the Description page of Project Settings.


#include "ScatterBlastPowerUpBase.h"

#include "Ship.h"


void AScatterBlastPowerUpBase::ActivatePowerUp(AShip* Player)
{
	Super::ActivatePowerUp(Player);
	Player->FireRate=ScatterShotFireRate;
	Player->ActivateScatterShot();
}

