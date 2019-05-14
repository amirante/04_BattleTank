// Copyright 2019, ALSN, LLC. All rights reserved

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#include "MyTankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AMyTankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank *GetControlledTank() const;

private:
	void BeginPlay() override;
	ATank *MyControlledTank = nullptr;
};
