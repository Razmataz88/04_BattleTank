// Copyright Razmataz Productions

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"


/**
* Sets default values for this component's properties
*/

UTankAimingComponent::UTankAimingComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

/**
* Initializes the LastFireTime so Players and AI cannot immediately fire when game starts
*/
void UTankAimingComponent::BeginPlay()
{
    LastFireTime = GetWorld()->GetTimeSeconds();
}

/**
* Initialises Barrel and Turret references
*/
void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

/**
* Called once ever frame
*/
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (RoundsLeft <= 0)
    {
        FiringState = EFiringState::OutOfAmmo;
    }
    else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
}

/**
* Returns the FiringState of the Tank
*/
EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

/**
* Returns the amount of ammo left of the Tank
*/
int32 UTankAimingComponent::GetRoundsLeft() const
{
    return RoundsLeft;
}

/**
* Calculates Hitlocation and velocity of the projectile 
*/
void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!Barrel) { return; }

    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

    //Calculate the OutLaunchVelocity
    if (UGameplayStatics::SuggestProjectileVelocity(
            this,
            OutLaunchVelocity,
            StartLocation,
            HitLocation,
            LaunchSpeed,
            false,
            0,
            0,
            ESuggestProjVelocityTraceOption::DoNotTrace
            )
        )
    {
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
    // if no solution found do nothing
}

/**
* Calculates the rotaion of the barrel and turret to move towards aimpoint
*/
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    if (!ensure(Barrel) || !ensure(Turret)) { return; }

    // Work-out difference between current barrel rotation, and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
    if (FMath::Abs(DeltaRotator.Yaw) < 180)
    {
        Turret->Rotate(DeltaRotator.Yaw);
    }
    else // Avoid going the long way
    {
        Turret->Rotate(-DeltaRotator.Yaw);
    }
}

/**
* Calculates if the reticule matches the direction of the barrel's aim
*/
bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }
    auto BarrelForward = Barrel->GetForwardVector();
    return !(BarrelForward.Equals(AimDirection, 0.01));
}

/**
* Spawns projectile and fires 
* Keeps track of Rounds left
*/
void UTankAimingComponent::FireProjectile()
{
    if (FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo)
    {
        if (!ensure(Barrel && ProjectileBlueprint)) { return; }
        // Spawn projectie at the socket location of the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Projectile"))
            );
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = GetWorld()->GetTimeSeconds();
        RoundsLeft--;
    }
}

