// Copyright 2019, ALSN, LLC. All rights reserved


#include "MyTankPlayerController.h"
#include "GameFramework/PlayerController.h"

ATank *AMyTankPlayerController::GetControlledTank() const
{
	ATank *OurTank = nullptr;
	OurTank = Cast<ATank>(GetPawn());

	if (OurTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank found a tank: %s"), *OurTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GetControlledTank didn't find a tank!"));
	}

	return OurTank;
}

void AMyTankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

}