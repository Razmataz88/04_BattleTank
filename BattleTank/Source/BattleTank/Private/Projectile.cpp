// Copyright Razmataz Productions

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

/**
* Sets default values
*/
AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(false);

    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->bAutoActivate = false;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovement->bAutoActivate = false;

    ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion"));
    ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

/**
* Called when the game starts or when spawned
*/
void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

/**
* When Projectile collides an explosion occurs and dammage is applied to the object the projectile hit
*/
void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * Otheromponent, FVector NormalImpulse, const FHitResult & Hit)
{
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
    ExplosionForce->FireImpulse();

    SetRootComponent(ImpactBlast);
    CollisionMesh->DestroyComponent();

    UGameplayStatics::ApplyRadialDamage(
        this,
        ProjectileDamage,
        GetActorLocation(),
        ExplosionForce->Radius, // for consistency
        UDamageType::StaticClass(),
        TArray<AActor*>() // damage all actors
    );

    FTimerHandle Timer;
    GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);

}

/**
* The projectile will be destroyed at a certain length of time after it collided with an object
*/
void AProjectile::OnTimerExpire()
{
    Destroy();
}

/**
* Applies a velocity and direction for the projectil to be launched
*/
void AProjectile::LaunchProjectile(float Speed)
{
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    ProjectileMovement->Activate();
}
