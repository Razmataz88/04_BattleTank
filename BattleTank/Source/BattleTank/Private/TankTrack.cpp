// Copyright Razmataz Productions

#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
    Throttle = FMath::Clamp<float>(Throttle, -1, 1);
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
