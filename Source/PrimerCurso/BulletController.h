// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BulletController.generated.h"

UCLASS()
class PRIMERCURSO_API ABulletController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Speed = 300.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
