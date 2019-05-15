// Copyright 2019, ALSN, LLC. All rights reserved


#include "TankPlayerController.h"
#include "GameFramework/PlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyControlledTank = GetControlledTank();
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
	if (!MyControlledTank) { return; }

	FVector HitLocation; // out parameter

	// Get world location if linetrace through crosshair
	// If it hits landscape, tell controlled tank to aim at this point
	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
		// TODO tell controlled tank to aim at this point
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
	
	FVector2D ScreenLocation;
	ScreenLocation.X = ViewportSizeX * CrossHairXLocation;
	ScreenLocation.Y = ViewportSizeY * CrossHairYLocation;
	
	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("LookDirection: [%f %f %f]"), LookDirection.X, LookDirection.Y, LookDirection.Z);
	}

	// Line-trace along that look direction and see what we hit (up to max range)
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector WorldLocationDummy;

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocationDummy, LookDirection);
}

ATank *ATankPlayerController::GetControlledTank() const
{
	ATank *OurTank = nullptr;
	OurTank = Cast<ATank>(GetPawn());

	if (OurTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank found a player controlled tank: %s"), *OurTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank didn't find a tank!"));
	}

	return OurTank;
}

