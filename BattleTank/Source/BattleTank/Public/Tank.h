// Copyright Razmataz Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ATank();
    
    UFUNCTION(BluePrintCallable, Category = "Firing")
    void FireProjectile();

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UFUNCTION(BluePrintCallable, Category = "Setup")
    void SetBarrelReference(UTankBarrel* BarrelToSet);

private:
    // Local barrel reference for spawning projectile
    UTankBarrel* Barrel = nullptr; //TODO remove
    double LastFireTime = 0;
};
