// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"

void AShipController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!bHasInitializedInputComponent)
	{
		InputComponent->BindAxis("Right", this, &AShipController::MoveRight);
		InputComponent->BindAxis("Forward", this, &AShipController::MoveForward);
		bHasInitializedInputComponent=true;
	}
}


void AShipController::MoveRight(float Value)
{
	if(Value!=0)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		GetPawn()->AddMovementInput(Direction, Value);

	}
}

void AShipController::MoveForward(float Value)
{
	if(Value!=0)
	{

		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		GetPawn()->AddMovementInput(Direction, Value);
	}
}

