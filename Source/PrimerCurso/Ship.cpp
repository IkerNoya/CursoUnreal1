// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"

#include <ThirdParty/CryptoPP/5.6.5/include/fips140.h>

#include "BulletController.h"
#include "EnemyController.h"
#include "PowerUpBase.h"
#include "ShipController.h"
#include "TopDownShooterGameMode.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Preferences/UnrealEdKeyBindings.h"

// Sets default values
AShip::AShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	CollisionBox->SetGenerateOverlapEvents(true);

	Shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	Shield->SetupAttachment(CollisionBox);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement Component"));
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	Shield->SetVisibility(false);

	BulletSpawnOffset = GetActorForwardVector() * 150;
	CurrentFireRate = FireRate;
}

void AShip::PostInitializeComponents() // delegates dinamicos relacionados con componentes van aca
{
	Super::PostInitializeComponents();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShip::OnOverlap);
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// PlayerInputComponent->BindAxis("Right", this, &AShip::MoveRight);
	// PlayerInputComponent->BindAxis("Forward", this, &AShip::MoveForward);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShip::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AShip::EndFire);

}

void AShip::StartFire()
{
	Fire(); //                              parametro siguiente: Delay
	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AShip::Fire, CurrentFireRate, true);
}

void AShip::Fire()
{
	UWorld* World = GetWorld();
	if (World)
	{
		if (bIsScatterShotActivated)
		{
			World->SpawnActor<ABulletController>(SineBullet, GetActorLocation() + BulletSpawnOffset, FRotator::ZeroRotator);
			World->SpawnActor<ABulletController>(SineBullet, GetActorLocation() + BulletSpawnOffset + FVector(-50,70,0), FRotator::ZeroRotator);
			World->SpawnActor<ABulletController>(SineBullet, GetActorLocation() + BulletSpawnOffset + FVector(-50,-70,0), FRotator::ZeroRotator);
		}
		else
		{
			World->SpawnActor<ABulletController>(NormalBullet, GetActorLocation() + BulletSpawnOffset, FRotator::ZeroRotator);
		}
	}
}

void AShip::EndFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}


void AShip::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemyController::StaticClass()) && !bIsDead)
	{
		if (!bIsShieldActivated)
		{
			bIsDead = true;
			UWorld* World = GetWorld();
			UGameplayStatics::SpawnEmitterAtLocation(World, Explosion, GetActorLocation(), FRotator::ZeroRotator, FVector(5,5,5), true);
			if (World)
			{
				ATopDownShooterGameMode* GameMode = Cast<ATopDownShooterGameMode>(World->GetAuthGameMode());
				if (GameMode)
				{
					GameMode->GameOver();
				}
			}
			Destroy();
		}
		else
		{
			AEnemyController* Enemy = Cast<AEnemyController>(OtherActor);
			if(ShieldHP>1)
			{
				if (Enemy)
				{
					Enemy->DestroyEnemy();
				}
				ShieldHP--;
				HitShield();
			}
			else
			{
				DeactivateShield();
				if (Enemy)
				{
					Enemy->DestroyEnemy();
				}
			}
		}
	}
	else if (OtherActor->IsA(APowerUpBase::StaticClass()) && !bIsDead)
	{
		APowerUpBase* PowerUp = Cast<APowerUpBase>(OtherActor);

		if (PowerUp)
		{
			switch (PowerUp->PowerUpType)
			{
			case ETypes::None:
				break;
			case ETypes::ScatterBlast:
				ActivateScatterShot();
				bActivateSineMovement = PowerUp->bActivateSineMovement;
				CurrentFireRate = PowerUp->ScatterShotFireRate;
				break;
			case ETypes::Shield:
				ActivateShield();
				ShieldHP = PowerUp->ShieldHP;
				break;
			default:
				break;
			}
		}
		OtherActor->Destroy();
		
	}
}

void AShip::ActivateShield()
{
	bIsShieldActivated = true;
	Shield->SetVisibility(true);
}

void AShip::DeactivateShield()
{
	bIsShieldActivated = false;
	Shield->SetVisibility(false);
}

void AShip::ActivateScatterShot()
{
	if(!bIsScatterShotActivated)
	{
		SetScatterShot();
	}
	GetWorld()->GetTimerManager().SetTimer(ScatterShotTimer, this, &AShip::SetScatterShot, ScatterShotTime, false);
}

void AShip::SetScatterShot()
{
	bIsScatterShotActivated = !bIsScatterShotActivated;
	if(!bIsScatterShotActivated)
	{
		CurrentFireRate = FireRate;
	}
}


void AShip::HitShield_Implementation()
{
	
}
void AShip::BeginDestroy()
{
	UWorld* World = GetWorld();
	if(World)
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimer);
		GetWorld()->GetTimerManager().ClearTimer(ScatterShotTimer);
	}
	Super::BeginDestroy();
}
