// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeSpeed);	// -1 is max counterclockwise? speed and +1 is max clockwise? speed

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 25;	// sensible default
};
