// Copyright Razmataz Productions

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declaration
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
    GENERATED_BODY()
    
public:
    
    virtual void Tick(float DeltaTime) override;

private:
    // How close can the Ai tank get
    float AcceptanceRadius = 3000;
};
