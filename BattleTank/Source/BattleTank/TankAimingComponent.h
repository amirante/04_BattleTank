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
	Reloading,
	OutOfAmmo
};

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Hold parameters for barrel properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire(bool IsAITank = false);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialiseComponent(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void MoveBarrelTowards(FVector AimDirection);
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	bool IsBarrelMoving();

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
	FVector AimDirection = FVector(0);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 0.1f;

	// Temporary flag to turn off AI Tank firing for debugging purposes
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	bool bCanAITanksFire = false;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 CurrentAmmo = 20;

	double LastFireTime = 0;
};
