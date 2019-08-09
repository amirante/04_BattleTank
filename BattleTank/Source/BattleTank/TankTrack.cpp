// Copyright 2019, ALSN, LLC. All rights reserved


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();

	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel *Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<class USceneComponent*>ChildrenList;
	TArray<class ASprungWheel*>ResultArray;

	GetChildrenComponents(true, ChildrenList);

	for (USceneComponent *Child : ChildrenList) {
		auto SpawnPointChild = Cast<USpawnPoint>(Child);

		if (!SpawnPointChild) continue;
		AActor *SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;
		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}
