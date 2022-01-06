// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = General)
	UShapeComponent* CollisionBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* Shield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	UPawnMovementComponent* PawnMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float FireRate= 0.5f;

	float CurrentFireRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PowerUps)
	float ScatterShotTime = 5;

	UPROPERTY(EditAnywhere, Category = Bullet)
	TSubclassOf<class ABulletController> NormalBullet;
	UPROPERTY(EditAnywhere, Category = Bullet)
	TSubclassOf<class ABulletController> SineBullet;
	UPROPERTY(VisibleAnywhere, Category=Bullet)
	bool bActivateSineMovement=false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	bool bIsDead = false;
	
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PowerUps)
	bool bIsShieldActivated = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PowerUps)
	bool bIsScatterShotActivated = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PowerUps)
	float ScatterShotFireRate=.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PowerUps)
	int ShieldHP=1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=VFX)
	UParticleSystem* PickUpParticles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=VFX)
	UParticleSystem* Explosion;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	FTimerHandle FireTimer;
	FTimerHandle ScatterShotTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void StartFire();
	void Fire();
	void EndFire();
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void ActivateShield();
	void DeactivateShield();
	void ActivateScatterShot();
	void SetScatterShot();

	UFUNCTION(BlueprintNativeEvent)
	void HitShield();
	void HitShield_Implementation();
	
	
	virtual void BeginDestroy() override;
	
private:
	FVector BulletSpawnOffset;
};
