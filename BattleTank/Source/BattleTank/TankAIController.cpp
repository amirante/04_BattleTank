// Copyright 2019, ALSN, LLC. All rights reserved

#include "TankAIController.h"
#include "Engine/World.h"
#include "MyTankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	MyControlledTank = GetControlledTank();

	Player0Tank = GetPlayerTank();
}

ATank *ATankAIController::GetControlledTank() const
{
	ATank *OurTank = nullptr;
	OurTank = Cast<ATank>(GetPawn());

	if (OurTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank found an AI tank: %s"), *OurTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank didn't find an AI tank!"));
	}

	return OurTank;
}


// Find the player's tank: assumes only single player game for now
// TODO: Change to support multiplayer
ATank * ATankAIController::GetPlayerTank() const
{
	ATank *OtherPlayerTank = nullptr;
	OtherPlayerTank = Cast<AMyTankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
	
	if (!OtherPlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController: Couldn't find Player tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found Player tank: %s"), *OtherPlayerTank->GetName());
	}
	return OtherPlayerTank;
}
