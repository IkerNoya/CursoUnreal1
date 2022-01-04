// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyController.generated.h"

UCLASS()
class PRIMERCURSO_API AEnemyController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed = 800.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};