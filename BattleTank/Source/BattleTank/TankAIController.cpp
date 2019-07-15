// Copyright 2019, ALSN, LLC. All rights reserved

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/AIModule/Classes/AIController.h"	// Depends on movement component via pathfinding system


ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn *InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("OnPossedTankDeath mcast received"));
	if (!ensure(GetPawn())) { return; }	// TODO remove ensure if ok
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto Player0Tank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto MyControlledTank = GetPawn();
	
	if (!ensure(MyControlledTank && Player0Tank)) { return; }

	// Move towards the player
	MoveToActor(Player0Tank, AcceptanceRadius);	// TODO check radius is in cm

	// Aim Towards Tank;
	auto AimingComponent = MyControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	AimingComponent->AimAt(Player0Tank->GetActorLocation());

	// Only if locked then fire
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked ||
		AimingComponent->GetFiringState() == EFiringStatus::Aiming) {
		AimingComponent->Fire(true);	// TODO remove true param when not debugging
	}
}

