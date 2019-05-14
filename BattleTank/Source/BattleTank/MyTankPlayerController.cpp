// Copyright 2019, ALSN, LLC. All rights reserved


#include "MyTankPlayerController.h"
#include "GameFramework/PlayerController.h"

void AMyTankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyControlledTank = GetControlledTank();
}

ATank *AMyTankPlayerController::GetControlledTank() const
{
	ATank *OurTank = nullptr;
	OurTank = Cast<ATank>(GetPawn());

	if (OurTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank found a player controlled tank: %s"), *OurTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank didn't find a tank!"));
	}

	return OurTank;
}

