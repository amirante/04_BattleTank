// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank *GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;	// Called every frame

private:
	void BeginPlay() override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	ATank *MyControlledTank = nullptr;
};
