// Copyright 2019, ALSN, LLC. All rights reserved


#include "MyTankPlayerController.h"
#include "GameFramework/PlayerController.h"

ATank *AMyTankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}