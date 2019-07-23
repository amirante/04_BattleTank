// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupConstraint();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent *MassWheelConstraint = nullptr;

	FConstraintInstance ConstraintInstance;
};
