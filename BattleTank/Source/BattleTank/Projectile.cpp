// Copyright 2019, ALSN, LLC. All rights reserved


#include "Projectile.h"
#include "Classes/Engine/World.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Classes/PhysicsEngine/RadialForceComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Classes/GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	//InitialLifeSpan = 4.0f;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent,
	FVector NormalImpulse, const FHitResult & Hit)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("TankDonkey: In AProjectile::OnHit [%s]"), *Name);
	
	LaunchBlast->Deactivate();
	ImpactBlast->Activate(true);
	ExplosionForce->FireImpulse();
	
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	// From the comments, not sure we need this
	/*TArray<AActor*> Ignore;
	Ignore.Add(this);*/

	UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, GetActorLocation(), ExplosionForce->Radius,
										UDamageType::StaticClass(), TArray<AActor*>());		// damage all actors

	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(THandle, this, &AProjectile::OnTimerExpire, DestroyDelay, false);

}

void AProjectile::OnTimerExpire()
{
	/*auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("TankDonkey: In AProjectile::OnTimerExpire [%s]"), *Name);*/
	Destroy();
}

void AProjectile::LaunchProjectile( float Speed)
{
	if (!ensure(ProjectileMovement)) { return; }

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}



