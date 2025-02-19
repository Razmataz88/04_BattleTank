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
    Locked,
    OutOfAmmo
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

/**
* Aiming Functionality for the Tank
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    void AimAt(FVector HitLocation);
    EFiringState GetFiringState() const;
    

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

    UFUNCTION(BluePrintCallable, Category = "Firing")
    void FireProjectile();
    
    UFUNCTION(BluePrintCallable, Category = "Firing")
    int32 GetRoundsLeft() const;


    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

protected:

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 RoundsLeft = 3;

private:

    UTankAimingComponent();

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    virtual void BeginPlay() override;

    void MoveBarrelTowards(FVector AimDirection);
    bool IsBarrelMoving();

    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    FVector AimDirection;
    double LastFireTime = 0;
};
