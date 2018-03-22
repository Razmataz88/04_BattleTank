// Copyright Razmataz Productions

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for Aiming state
UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTankAimingComponent();

    void AimAt(FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);


    UFUNCTION(BluePrintCallable, Category = "Firing")
    void FireProjectile();

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Aiming;

private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    double LastFireTime = 0;

    //UTankAimingComponent();
    void MoveBarrelTowards(FVector AimDirection);

};
