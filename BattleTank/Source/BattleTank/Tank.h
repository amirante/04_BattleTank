// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class AProjectile;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector HitLocation);
	
	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//void SetBarrelReference(UTankBarrel *BarrelToSet);

	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//void SetTurretReference(UTankTurret *TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire(bool IsAITank=false);

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent *TankAimingComponent = nullptr;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	// Temporary flag to turn off AI Tank firing for debugging purposes
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	bool CanAITanksFire = false;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// TODO Remove Barrel reference
	UTankBarrel *Barrel = nullptr;	// Local barrel reference for spawning projecile
	double LastFireTime = 0;

	void BeginPlay() override;
};
