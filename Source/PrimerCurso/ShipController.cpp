// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"
#include "Ship.h"

#include "Kismet/GameplayStatics.h"

AShipController::AShipController()
{
	bAutoManageActiveCameraTarget=false;
}

void AShipController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!bHasInitializedInputComponent)
	{
		InputComponent->BindAxis("Right", this, &AShipController::MoveRight);
		InputComponent->BindAxis("Forward", this, &AShipController::MoveForward);

		InputComponent->BindAction("Reset", IE_Pressed, this,&AShipController::OnResetPressed);
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

		if(IsValid(GetPawn()))
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
		if(IsValid(GetPawn()))
			GetPawn()->AddMovementInput(Direction, Value);
	}
}

void AShipController::OnResetPressed()
{
	if(IsValid(GetPawn()))
	{
		UnPossess();
	}
	if(!IsValid(GetPawn()))
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

