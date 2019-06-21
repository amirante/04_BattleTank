// Copyright 2019, ALSN, LLC. All rights reserved


#include "Projectile.h"
#include "Classes/Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;

	// Following added from FPSProject
	ProjectileMovement->SetUpdatedComponent(CollisionMesh);
	ProjectileMovement->InitialSpeed = 10000.0f;
	ProjectileMovement->MaxSpeed = 10000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	//ProjectileMovement->bShouldBounce = true;
	//ProjectileMovement->Bounciness = 0.3f;
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::LaunchProjectile( float Speed)
{
	if (!ensure(ProjectileMovement)) { return; }

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



