// Copyright Razmataz Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward Declarations
class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
    GENERATED_BODY()
    
public:

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

    UFUNCTION(BluePrintCallable, Category = "Input")
    void IntendMoveForward(float Throw);
    
    UFUNCTION(BluePrintCallable, Category = "Input")
    void IntendTurnRight(float Throw);

private:

    virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;

    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;

};
