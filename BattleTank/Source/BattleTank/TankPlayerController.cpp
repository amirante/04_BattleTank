// Copyright 2019, ALSN, LLC. All rights reserved

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Classes/Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//MyControlledTank = GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) {	return; }
	
	FoundAimingComponent(AimingComponent);
}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // out parameter

	// Get world location of linetrace through crosshair
	// If it hits landscape, tell controlled tank to aim at this point
	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());
		//MyControlledTank->AimAt(HitLocation);
		AimingComponent->AimAt(HitLocation);
	}
	else {
		// miss
	}
}

// Get world location of linetrace through crosshair, returns true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that look direction and see what we hit (up to max range)
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation)) {
			// do something here?
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)) {
		// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);	// aiming at the sky so return nothing
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector WorldLocationDummy;

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocationDummy, LookDirection);
}

//ATank *ATankPlayerController::GetControlledTank() const
//{
//	APawn *OurTank = nullptr;
//	OurTank = GetPawn();
//
//	if (OurTank != nullptr) {
//		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank found a player controlled tank: %s"), *OurTank->GetName());
//	}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank didn't find a tank!"));
//	}
//
//	return OurTank;
//}

