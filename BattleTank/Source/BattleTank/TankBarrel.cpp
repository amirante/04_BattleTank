// Copyright 2019, ALSN, LLC. All rights reserved


#include "TankBarrel.h"

void
UTankBarrel::Elevate(float DegreesPerSecond)
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed and frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel::Elevate called at speed %f"), DegreesPerSecond);
}