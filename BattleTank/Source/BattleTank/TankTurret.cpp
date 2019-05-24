// Copyright 2019, ALSN, LLC. All rights reserved


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move the turret the right amount this frame

	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto RotationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}