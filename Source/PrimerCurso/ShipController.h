// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShipController.generated.h"

/**
 * 
 */
UCLASS()
class PRIMERCURSO_API AShipController : public APlayerController
{
	GENERATED_BODY()
	bool bHasInitializedInputComponent=false;
public:
	virtual void SetupInputComponent() override;
	
	void MoveRight(float Value);
	void MoveForward(float Value);
};
