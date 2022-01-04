// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"

#include "BulletController.h"
#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	CollisionBox->SetGenerateOverlapEvents(true);
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement Component"));
	
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();

	BulletSpawnOffset = GetActorForwardVector() * 150;
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
	PlayerInputComponent->BindAxis("Right", this, &AShip::MoveRight);
    PlayerInputComponent->BindAxis("Forward", this, &AShip::MoveForward);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShip::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &AShip::EndFire);
	
}

void AShip::MoveRight(float Value)
{
	if(Value && !IsDead)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AShip::MoveForward(float Value)
{
	if(Value && !IsDead)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AShip::StartFire()
{
	if(!IsDead)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AShip::Fire, FireRate, true);
	}
}

void AShip::Fire()
{
	UWorld* World = GetWorld();
	if(World)
	{
		World->SpawnActor<ABulletController>(Bullet, GetActorLocation() + BulletSpawnOffset, FRotator::ZeroRotator);
	}
}

void AShip::EndFire()
{
	if(!IsDead)
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimer);
	}
}

void AShip::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AEnemyController::StaticClass()) && !IsDead)
	{
		IsDead =true;
		GetWorld()->GetTimerManager().ClearTimer(FireTimer);
	}
}
