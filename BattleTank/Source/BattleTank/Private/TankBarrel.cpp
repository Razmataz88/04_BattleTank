// Copyright Razmataz Productions

#include "TankBarrel.h"
#include "BattleTank.h"

/**
* Moves the Barrel up or down at a Relative speed
*/
void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move the barrel the right amount this frame
    // Given a max elevation speed, and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationInDegrees, MaxElevationInDegrees);

    SetRelativeRotation(FRotator(Elevation, 0, 0));
}

