// Copyright Razmataz Productions

#include "Tank.h"
#include "BattleTank.h"

/**
* Sets default values
*/
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

/**
* Begin Play
*/
void ATank::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = StartingHealth;
}

/**
* Override function to calculate damage taken from projectile
*/
float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
    
    CurrentHealth -= DamageToApply;

    if (CurrentHealth <= 0)
    {
        OnDeath.Broadcast();
    }
    return DamageToApply;
}

/**
* Returns health left of Tank
*/
float ATank::GetHealthPercent() const
{
    return (float)CurrentHealth / (float)StartingHealth;
}