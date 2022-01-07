// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"

#include "Ship.h"
#include "GameFramework/Actor.h"
#include "PowerUpBase.generated.h"


UENUM(BlueprintType)
enum class ETypes : uint8
{
	None, ScatterBlast, Shield, Nuke
};
UCLASS(Abstract)
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	UParticleSystem* PickUpParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float TimeToDestroy = 5;

	FTimerHandle TimerToDestroy;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void ActivatePowerUp(AShip* Player);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DestroyPowerUp();
	
	UFUNCTION() // NO OLVIDARSE NUNCA MAS
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
