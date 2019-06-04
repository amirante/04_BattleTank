// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.generated.h"


class ATank;

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

	// How close can the AI tank get to the player
	float AcceptanceRadius = 3000.0f;	// assume it is in centimeters
};
