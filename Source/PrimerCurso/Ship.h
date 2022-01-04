// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Distributions/DistributionFloatUniformCurve.h"
#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

class UFloatingPawnMovement;

UCLASS()
class PRIMERCURSO_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();

	UPROPERTY(EditAnywhere, Category = General)
	UShapeComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	UPawnMovementComponent* PawnMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float FireRate= 0.5f;

	UPROPERTY(EditAnywhere, Category = Bullet)
	TSubclassOf<class ABulletController> Bullet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	bool IsDead = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	FTimerHandle FireTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float Value);
	void MoveForward(float Value);
	void StartFire();
	void Fire();
	void EndFire();
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector BulletSpawnOffset;
};
