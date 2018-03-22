// Copyright Razmataz Productions

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if (!ensure(PlayerTank && ControlledTank)) { return; }

    // Move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm

    // Aim towards the player
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    EFiringState FiringState = AimingComponent->GetFiringState();

    if (FiringState == EFiringState::Locked)
    {
        AimingComponent->FireProjectile();
    }
}


