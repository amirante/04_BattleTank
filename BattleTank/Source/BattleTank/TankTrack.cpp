// Copyright 2019, ALSN, LLC. All rights reserved


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	auto Name = GetName();

	UE_LOG(LogTemp, Warning, TEXT("%s: SetThrottle at %f"), *Name, Throttle);
}