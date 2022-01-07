// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyController.generated.h"

UCLASS()
class PRIMERCURSO_API AEnemyController : public AActor // Nombre de mierda, cambiar a algo ocn sentido
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed = 800.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	FVector Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	bool bIsDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool bIsInmuneToNuke = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	UParticleSystem* Explosion;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DestroyEnemy();
	

};
