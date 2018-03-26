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
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATankAIController : public AAIController
{
    GENERATED_BODY()
    
public:
    
protected:
    // How close can the Ai tank get
    UPROPERTY(EditAnywhere, Category = "Setup") // Consider EditDefaultsOnly
    float AcceptanceRadius = 8000;

private:
    virtual void Tick(float DeltaTime) override;
    virtual void SetPawn(APawn* InPawn) override;

    UFUNCTION()
    void OnPossessedTankDeath();
};
