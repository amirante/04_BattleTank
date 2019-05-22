// Copyright 2019, ALSN, LLC. All rights reserved

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	MyControlledTank = GetControlledTank();

	Player0Tank = GetPlayerTank();	// TODO Change this for multiplayer
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


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (MyControlledTank) {
		// TODO Move towards the player

		//AimTowardsTank();
		MyControlledTank->AimAt(Player0Tank->GetActorLocation());

		// Fire if ready
	}
}



// Find the player's tank: assumes only single player game for now
// TODO: Change to support multiplayer
ATank * ATankAIController::GetPlayerTank() const
{
	ATank *OtherPlayerTank = nullptr;
	OtherPlayerTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
	
	if (!OtherPlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController: Couldn't find Player tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found Player tank: %s"), *OtherPlayerTank->GetName());
	}
	return OtherPlayerTank;
}
