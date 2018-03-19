// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
    auto Time = GetWorld()->GetTimeSeconds();
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("%f: %s Throttle: %f"), Time, *Name, Throttle);

    // TODO Clamp Incoming Throttle values between -1 and +1
}
