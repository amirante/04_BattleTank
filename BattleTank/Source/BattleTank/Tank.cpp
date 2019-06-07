// Copyright 2019, ALSN, LLC. All rights reserved


#include "Tank.h"
#include "TankBarrel.h"
#include "GameFramework/Actor.h"
#include "Classes/Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Engine/StaticMeshSocket.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);	// delegate aiming stuff to subobject
}


void ATank::Fire(bool IsAITank)
{
	bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds;

	auto World = GetWorld();
	if (!World) { return; }

	if ( Barrel && isReloaded ) {
		// Spawn a projectile at the socket location on the barrel
		const UStaticMeshSocket *BarrelSocket = Barrel->GetSocketByName("Projectile");

		// remove this if statement for final build. This is just for debugging to turn off AI tanks shooting
		if ( !IsAITank || CanAITanksFire ) {
			auto Projectile = World->SpawnActor<AProjectile>(ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile")));

				Projectile->LaunchProjectile(LaunchSpeed);
		}

		LastFireTime = FPlatformTime::Seconds();	// or use GetWorld()->GetTimeSeconds();
	}
}


