// Copyright 2019, ALSN, LLC. All rights reserved


#include "SprungWheel.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Mass);

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	MassWheelConstraint->SetupAttachment(Mass);

	/*MassWheelConstraint->ConstraintInstance = ConstraintInstance;
	MassWheelConstraint->ConstraintInstance.bLinearLimitSoft_DEPRECATED = 1;

	MassWheelConstraint->SetConstrainedComponents(Mass, "Mass", Wheel, "Wheel");
	MassWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.0);
	MassWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0);
	MassWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0);
	MassWheelConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.0);
	MassWheelConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.0);
	MassWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 100.0);*/

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

