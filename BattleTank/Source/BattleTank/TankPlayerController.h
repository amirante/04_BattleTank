// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//class ATank;
class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent *AimCompRef);

private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn *InPawn) override;

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

	UFUNCTION()
	void OnPossessedTankDeath();

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;
};
