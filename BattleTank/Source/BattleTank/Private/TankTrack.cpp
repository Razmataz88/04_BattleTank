// Copyright Razmataz Productions

#include "TankTrack.h"

/**
* Constructor
*/
UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
    
}

/**
*  BeginPlay
*/
void UTankTrack::BeginPlay()
{
    Super::BeginPlay();

    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


/**
* Applys a SidewaysForce to controll the tank from "slipping" sideways
*/
void UTankTrack::ApplySidewaysForce()
{
    auto DeltaTime = GetWorld()->GetDeltaSeconds();

    // Calculate the slippage speed
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    
    // Work-out the required acceleration this frame to correct
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    
    //Calculate and apply sideways force (F = m a)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration;

    TankRoot->AddForce(CorrectionForce);
}

/**
* 
*/
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* Otheromponent, FVector NormalImpulse, const FHitResult& Hit)
{
    DriveTrack();
    ApplySidewaysForce();

    // reset the throttle
    CurrentThrottle = 0;
}

/**
* Set's the Throttle of the track
*/
void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

/**
* Applys Forces to the origin point of the track
*/
void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}