// Copyright 2019, ALSN, LLC. All rights reserved

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "TankPlayerController.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//MyControlledTank = GetControlledTank();

	//Player0Tank = GetPlayerTank();	// TODO Change this for multiplayer
}

//ATank *ATankAIController::GetControlledTank() const
//{
//	ATank *OurTank = nullptr;
//	OurTank = Cast<ATank>(GetPawn());
//
//	if (OurTank != nullptr) {
//		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank found an AI tank: %s"), *OurTank->GetName());
//	}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank didn't find an AI tank!"));
//	}
//
//	return OurTank;
//}


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

	// Fire if ready
	// TODO Fix Firing
	//MyControlledTank->Fire(true);	// TODO remove true param when not debugging
}



// Find the player's tank: assumes only single player game for now
// TODO: Change to support multiplayer
//ATank * ATankAIController::GetPlayerTank() const
//{
//	ATank *OtherPlayerTank = nullptr;
//	OtherPlayerTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetPawn();
//	
//	if (!OtherPlayerTank) {
//		UE_LOG(LogTemp, Warning, TEXT("TankAIController: Couldn't find Player tank!"));
//	}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT("TankAIController found Player tank: %s"), *OtherPlayerTank->GetName());
//	}
//	return OtherPlayerTank;
//}
