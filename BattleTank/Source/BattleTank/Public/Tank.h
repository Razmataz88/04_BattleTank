// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ATank();

    void AimAt(FVector HitLocation);
    
    UFUNCTION(BluePrintCallable, Category = Firing)
    void FireProjectile();
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float LaunchSpeed = 4000; 

    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float ReloadTimeInSeconds = 3;

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UFUNCTION(BluePrintCallable, Category = Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet);

    UFUNCTION(BluePrintCallable, Category = Setup)
    void SetTurretReference(UTankTurret* TurretToSet);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly)
    UTankAimingComponent* TankAimingComponent = nullptr;
    
    UPROPERTY(BlueprintReadOnly)
    UTankMovementComponent* TankMovementComponent = nullptr;

private:
    // Local barrel reference for spawning projectile
    UTankBarrel* Barrel = nullptr;
    double LastFireTime = 0;
};
