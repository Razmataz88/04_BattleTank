// Copyright Razmataz Productions


#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!ensure (LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);

    // TODO prevent double-speed due to dual input
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if ( !ensure (LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);

    // TODO prevent double-speed due to dual input
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
    
    auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
    auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;
    
    IntendMoveForward(ForwardThrow);
    IntendTurnRight(RightThrow);
}
