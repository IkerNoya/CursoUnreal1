// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldPowerUpBase.h"

#include "Ship.h"


void AShieldPowerUpBase::ActivatePowerUp(AShip* Player)
{
	Super::ActivatePowerUp(Player);
	Player->ActivateShield();
	Player->ShieldHP=Hp;
}
