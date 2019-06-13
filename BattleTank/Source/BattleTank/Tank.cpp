// Copyright 2019, ALSN, LLC. All rights reserved


#include "Tank.h"


ATank::ATank()
{
	auto TankName = GetName();

	UE_LOG(LogTemp, Warning, TEXT("TankDonkey: In ATank::ATank [%s]"), *TankName);
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}
