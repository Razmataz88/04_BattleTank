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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    void AimAt(FVector HitLocation, float LaunchSpeed);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Aiming;

private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    UTankAimingComponent();
    void MoveBarrelTowards(FVector AimDirection);

};
