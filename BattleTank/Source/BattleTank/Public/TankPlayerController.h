// Copyright Razmataz Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward Declarations
class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
    GENERATED_BODY()
    
protected:

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

    UFUNCTION()
    void OnPossessedTankDeath();

private:

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetPawn(APawn * InPawn) override;

    // Start the tank moving the barrel so that a shot would 
    // hit where the crosshair intersects the world
    void AimTowardsCrosshair();
    
    bool IsSightRayHitLocation(FVector& HitLocation) const;
    bool IsLookDirectionValid(FVector2D ScreenLocation, FVector & LookDirection) const;
    bool IsLookVectorHitLocationValid(FVector& LookDirection, FVector& HitLocation) const;

    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5;

    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333;

    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 100000000000.0;
};
