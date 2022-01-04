// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"

#include "../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/fmt/bundled/printf.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/MovementComponent.h"

// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement Component"));
	
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
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
	if(Value)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AShip::MoveForward(float Value)
{
	if(Value)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}



