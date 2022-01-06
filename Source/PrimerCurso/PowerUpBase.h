// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PowerUpBase.generated.h"


UENUM(BlueprintType)
enum class ETypes : uint8
{
	None, ScatterBlast, Shield
};

UCLASS()
class PRIMERCURSO_API APowerUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpBase();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PowerUp)
	ETypes PowerUpType;
	
	UPROPERTY(EditAnywhere, Category = Collision)
	USphereComponent* SphereCollider;


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
