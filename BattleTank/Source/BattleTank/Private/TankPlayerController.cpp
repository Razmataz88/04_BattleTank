// Copyright Razmataz Productions

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"

/**
* BeginPlay
*/
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    FoundAimingComponent(AimingComponent);
}

/**
* Tick Called every frame
*/
void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

/**
* 
*/
void ATankPlayerController::SetPawn(APawn * InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }
        // TODO Subscribe to our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
    }
}

/**
* Calculates a HitLocation for the barrel and turret to aim towards
*/
void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()) { return; } // if not possessing

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    
    FVector HitLocation; // Out parameter
    bool bGotHitLocation = IsSightRayHitLocation(HitLocation);

    if (bGotHitLocation) // Has "Side-effect, is going to line trace
    {
        AimingComponent->AimAt(HitLocation);
    }
}

/**
* Get world location of linetrace through crosshair, true if hits landscape
*/ 
bool ATankPlayerController::IsSightRayHitLocation(FVector& HitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    FVector LookDirection;
    if (IsLookDirectionValid(ScreenLocation, LookDirection))
    {
        // line trance along that look direction, and see what we hit
        return IsLookVectorHitLocationValid(LookDirection, HitLocation);
    }
    
    return false;
}

/**
* Calculates the world direction from the Playercontrolers UI
*/
bool ATankPlayerController::IsLookDirectionValid(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;

    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

/**
* Calculates a RayCast. Returns true if valid hit location is found, otherwise falses
*/
bool ATankPlayerController::IsLookVectorHitLocationValid(FVector& LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(
                HitResult,
                StartLocation,
                EndLocation,
                ECollisionChannel::ECC_Camera)
        )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false;
}

/**
* Player Becomes a Spectator upon tank death
*/
void ATankPlayerController::OnPossessedTankDeath()
{
    StartSpectatingOnly();
}