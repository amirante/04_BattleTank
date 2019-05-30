// Copyright 2019, ALSN, LLC. All rights reserved


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto ClampedThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);

	auto ForceApplied = GetForwardVector() * ClampedThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	
}