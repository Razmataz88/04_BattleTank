// Copyright Razmataz Productions

#include "TankAIController.h"
#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"

/**
* Tick called once every frame
*/
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

/**
* Called when pawn is set so a delegate can be set on the pawn
*/
void ATankAIController::SetPawn(APawn * InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }
        // TODO Subscribe to our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}

/**
* Removes Ai control of tank upon death
*/
void ATankAIController::OnPossessedTankDeath()
{
    if (!ensure(GetPawn())) { return; }
    GetPawn()->DetachFromControllerPendingDestroy();
}


