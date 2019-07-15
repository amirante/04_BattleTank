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
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	int32 DamagePoints = FPlatformMath::RoundToInt(ActualDamage);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("TankDonkey: In ATank::TakeDamage DamageAmount [%f] DamageToApply [%i]"), 
		DamageAmount, DamageToApply);
	
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("TankDonkey: In ATank::TakeDamage: Tank Died!"));
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
