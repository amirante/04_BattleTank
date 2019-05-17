// Copyright 2019, ALSN, LLC. All rights reserved

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	// Calculate OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity,
									StartLocation, HitLocation, LaunchSpeed, false,0,0,
									ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out the difference between current barrel rotation and AimDirection
	
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator = [%s]"), *AimAsRotator.ToCompactString());
	
	// Move the barrel the right amount this frame
	// Given a max elevation speed and frame time
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}


