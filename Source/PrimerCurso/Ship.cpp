// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"

#include "../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/fmt/bundled/printf.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/MovementComponent.h"

// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Speed = 50.0f;
	
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
	if(!CurrentVelocity.IsZero())
	{
		FVector NewPosition = GetActorLocation() + Speed * CurrentVelocity * DeltaTime;
		SetActorLocation(NewPosition);
	}
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Right", this, &AShip::MoveRight);
	PlayerInputComponent->BindAxis("Forward", this, &AShip::MoveForward);
}

void AShip::MoveRight(float Value)
{
	CurrentVelocity.Y = Value * 100.0f;
}

void AShip::MoveForward(float Value)
{
	CurrentVelocity.X = Value * 100.0f;
}



