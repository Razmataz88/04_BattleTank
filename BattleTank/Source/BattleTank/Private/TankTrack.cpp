// Copyright Razmataz Productions

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
    
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();

    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Calculate the slippage speed
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    // Work-out the required acceleration this frame to correct
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    //Calculate and apply sideways force (F = m a)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration;
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* Otheromponent, FVector NormalImpulse, const FHitResult& Hit)
{

}

void UTankTrack::SetThrottle(float Throttle)
{
    Throttle = FMath::Clamp<float>(Throttle, -1, 1);
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
