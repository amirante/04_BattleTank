// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

protected:
	ATankAIController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	// How close can the AI tank get to the player
	float AcceptanceRadius = 8000.0f;	// assume it is in centimeters
};
