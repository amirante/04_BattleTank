// Copyright 2019, ALSN, LLC. All rights reserved

#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	auto Name = GetName();

	UE_LOG(LogTemp, Warning, TEXT("TankDonkey: In UTankAimingComponet::UTankAimingComponent [%s]"), *Name);
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("TankDonkey: In UTankAimingComponet::BeginPlay [%s]"), *Name);

	// so that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();	// or use GetWorld()->GetTimeSeconds();
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	FVector BarrelForward = Barrel->GetForwardVector();

	if (BarrelForward.Equals(AimDirection, 0.01)) {
		return false;
	}
	else {
		return true;
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("TankDonkey: In UTankAimingComponet::TickComponent [%s]"), *Name);

	if (CurrentAmmo <= 0) {
		FiringState = EFiringStatus::OutOfAmmo;
	}
	// TODO or use GetWorld()->GetTimeSeconds() instead of FPlatformTime::Seconds
	else if ( (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringStatus::Aiming;
	}

	else {
		FiringState = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector OutLaunchVelocity(0);
	
	// Calculate OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity,
									StartLocation, HitLocation, LaunchSpeed, false,0,0,
									ESuggestProjVelocityTraceOption::DoNotTrace)) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
	else {	// no solution found
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f AimAt: No aim solve found"), Time);
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	// Work out the difference between current barrel rotation and AimDirection
	
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	
	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}

	// NEW CODE - Turret Rotation - calculate Yaw ourselves instead of using Yaw from AimRotator
	/* FVector BarrelLocation = Barrel->GetComponentLocation();
	FRotator YawRotator = (AimDirection - BarrelLocation).Rotation();
	FRotator DeltaRotator = YawRotator - BarrelRotator;
	Turret->Rotate(FMath::Abs(DeltaRotator.Yaw) < 180 ? DeltaRotator.Yaw : -DeltaRotator.Yaw); */
}


void UTankAimingComponent::InitialiseComponent(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire(bool IsAITank)
{
	auto World = GetWorld();
	if (!ensure(World)) { return; }

	if (FiringState == EFiringStatus::Locked || FiringState == EFiringStatus::Aiming) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		// Spawn a projectile at the socket location on the barrel
		const UStaticMeshSocket *BarrelSocket = Barrel->GetSocketByName("Projectile");

		// remove this if statement for final build. This is just for debugging to turn off AI tanks shooting
		if (!IsAITank || CanAITanksFire) {
			auto Projectile = World->SpawnActor<AProjectile>(ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile")));

			Projectile->LaunchProjectile(LaunchSpeed);
			CurrentAmmo--;
		}

		LastFireTime = FPlatformTime::Seconds();	// or use GetWorld()->GetTimeSeconds();
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return CurrentAmmo;
}

