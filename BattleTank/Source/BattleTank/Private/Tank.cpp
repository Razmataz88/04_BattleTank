// Copyright Razmataz Productions

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "BattleTank.h"

// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

void ATank::FireProjectile()
{
    if (!ensure(Barrel)) { return; }

    bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

    if (isReloaded) 
    {
    // Spawn projectie at the socket location of the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Projectile"))
            );
        Projectile->LaunchProjectile(30000);
        LastFireTime = GetWorld()->GetTimeSeconds();
    }
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
    Barrel = BarrelToSet;
   
}
