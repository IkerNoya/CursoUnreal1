// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PowerUpBase.generated.h"


UENUM()
enum  class ETypes
{
	ScatterBlast, Shield
};

UCLASS()
class PRIMERCURSO_API APowerUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpBase();
	//ShereCOll
	//Mesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PowerUp)
	ETypes PowerUpType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh)
	UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere, Category = Collision)
	USphereComponent* SphereCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
