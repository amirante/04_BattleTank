// Copyright 2019, ALSN, LLC. All rights reserved


#include "TankAIController.h"

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

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));

}