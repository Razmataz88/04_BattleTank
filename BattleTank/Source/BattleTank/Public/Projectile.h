// Copyright Razmataz Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    AProjectile();
    void LaunchProjectile(float Speed);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* CollisionMesh = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* LaunchBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* ImpactBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    URadialForceComponent* ExplosionForce = nullptr;

private:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    void OnTimerExpire();

    UFUNCTION()
    void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * Otheromponent, FVector NormalImpulse, const FHitResult & Hit);

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ProjectileDamage = 20.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float DestroyDelay = 10.0f;

    UProjectileMovementComponent* ProjectileMovement = nullptr;

};
