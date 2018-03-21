// Copyright Razmataz Productions

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
    GENERATED_BODY()
public:
    //-1 is max downward speed, and +1 is max up movement
    void Elevate(float RelativeSpeed);
    
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MinElevationInDegrees = 0;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxElevationInDegrees = 40;
    
};