// Copyright 2019, ALSN, LLC. All rights reserved


#include "Tank.h"
#include "TankBarrel.h"
#include "GameFramework/Actor.h"
#include "Classes/Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Engine/StaticMeshSocket.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);	// delegate aiming stuff to subobject
}

void ATank::SetBarrelReference(UTankBarrel *BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret *TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("In ATank::Fire()"));

	auto World = GetWorld();
	if (!World) { return; }

	if (!Barrel) { return; }

	// Spawn a projectile at the socket location on the barrel
	const UStaticMeshSocket *BarrelSocket = Barrel->GetSocketByName("Projectile");

	auto Projectile = World->SpawnActor<AProjectile>(ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));

	Projectile->LaunchProjectile(LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

