// Copyright Razmataz Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    AProjectile();
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    void LaunchProjectile(float Speed);

protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CollisionMesh = nullptr;

    UPROPERTY(VisibleAnywhere)
    UParticleSystemComponent* LaunchBlast = nullptr;


private:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UProjectileMovementComponent* ProjectileMovement = nullptr;

};
