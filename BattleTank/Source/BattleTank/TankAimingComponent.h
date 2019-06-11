// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 
{ 
	Locked, 
	Aiming, 
	Reloading 
};

// Forward Declarations
class UTankBarrel;
class UTankTurret;

// Hold parameters for barrel properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void AimAt(FVector HitLocation, float LaunchSpeed);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialiseComponent(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
};
