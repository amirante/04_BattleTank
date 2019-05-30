// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = ( Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeComponent(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);
	
private:
	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;

};
