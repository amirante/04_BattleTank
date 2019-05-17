// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);
	void SetBarrelReference(UStaticMeshComponent *BarrelToSet);

	// TODO add SetTurretReference

protected:

private:
	UStaticMeshComponent *Barrel = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
		
};
