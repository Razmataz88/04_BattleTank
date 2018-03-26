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
    
public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:
    virtual void BeginPlay() override;

   

    // Start the tank moving the barrel so that a shot would 
    // hit where the crosshair intersects the world
    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector& HitLocation) const;
    bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
    bool GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const;

    void OnPossessedTankDeath();

    UFUNCTION()
    void SetPawn(APawn * InPawn);

    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5;

    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333;

    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 100000000000.0;
};
