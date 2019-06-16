// Copyright 2019, ALSN, LLC. All rights reserved


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, 
						FVector NormalImpulse, const FHitResult & Hit)
{
	/*auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("TankDonkey: In UTankTrack::OnHit [%s]"), *Name);*/

	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce() 
{
	// Work out the required acceleration this frame to correct

	auto RightVector = GetRightVector();
	auto ForwardVelocity = GetComponentVelocity();
	auto SlippageSpeed = FVector::DotProduct(RightVector, ForwardVelocity);
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime * RightVector);

	// Calculate and apply sideways force (F= ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;	// div 2 because there are 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
	//auto ClampedThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);

	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
