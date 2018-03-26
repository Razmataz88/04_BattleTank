// Copyright Razmataz Productions

#include "TankTurret.h"


/**
* Rotates the Tank Turret at a relative speed
*/
void UTankTurret::Rotate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}