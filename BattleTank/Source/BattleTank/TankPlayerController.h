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
	

private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	// Called every frame
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

	ATank *MyControlledTank = nullptr;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

};
