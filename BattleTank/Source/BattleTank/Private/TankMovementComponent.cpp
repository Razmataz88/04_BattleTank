// Copyright Razmataz Productions


#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"


/**
* Sets a reference to the left and right tracks
*/
void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

/**
* Applies a Throttle to each of the tracks to propel the tank forward/backward
*/
void UTankMovementComponent::IntendMoveForward(float Throttle)
{
    if (!ensure (LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throttle);
    RightTrack->SetThrottle(Throttle);
}

/**
* Applies a Throttle to each of the tracks to propel the tank right/left
*/
void UTankMovementComponent::IntendTurnRight(float Throttle)
{
    if ( !ensure (LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throttle);
    RightTrack->SetThrottle(-Throttle);
}

/**
* Function for AI movement
*/
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
    
    auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
    auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;
    
    IntendMoveForward(ForwardThrow);
    IntendTurnRight(RightThrow);
}
