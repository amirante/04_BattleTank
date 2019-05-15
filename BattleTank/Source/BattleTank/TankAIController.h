// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank *GetPlayerTank() const;
	ATank *GetControlledTank() const;
	ATank *Player0Tank = nullptr;	// TODO Change this to support multiplayer
	ATank *MyControlledTank = nullptr;
	float LineTraceRange = 1000000.0f;
};
