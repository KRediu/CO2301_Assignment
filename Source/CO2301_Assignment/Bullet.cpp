// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(RootComponent);
    
    BulletMesh->SetSimulatePhysics(false); // Disable physics simulation - prevents bouncing and phasing through walls
	BulletMesh->SetNotifyRigidBodyCollision(true);
    BulletMesh->BodyInstance.bNotifyRigidBodyCollision = true;
    BulletMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BulletMesh->SetCollisionResponseToAllChannels(ECR_Block); // Blocks all collisions

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
    ProjectileMovement->ProjectileGravityScale = 0.0f;
	InitialLifeSpan = 1.5f;

}


// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorHit.AddDynamic(this, &ABullet::OnHit);
}

void ABullet::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
	const FHitResult& Hit) {
    if (!OtherActor || OtherActor == this) return;

    UE_LOG(LogTemp, Warning, TEXT("Bullet hit: %s"), *OtherActor->GetName());

    AActor* ProjectileOwner = GetOwner();
    if (!ProjectileOwner) return;

    // Apply standard damage to all actors that support it
    UGameplayStatics::ApplyDamage(
        OtherActor,
        10.0f,
        ProjectileOwner->GetInstigatorController(),
        this,
        UDamageType::StaticClass()
    );

    // Check if the hit actor has a destructible component
    //if (UGeometryCollectionComponent* ChaosComponent = OtherActor->FindComponentByClass<UGeometryCollectionComponent>()) {
    //    FVector HitLocation = Hit.ImpactPoint;
    //    FVector HitDirection = Hit.ImpactNormal;

    //    // Apply a radial impulse to break Chaos destructible meshes
    //    ChaosComponent->AddRadialImpulse(HitLocation, 500.0f, 1000.0f, ERadialImpulseFalloff::RIF_Linear, true);

    //    UE_LOG(LogTemp, Warning, TEXT("Chaos destructible mesh hit!"));
    //}

    //if (OtherActor->IsA(AStaticMeshActor::StaticClass())) {
    //    // Destroy the mesh actor (it'll die immediately on hit)
    //    OtherActor->Destroy();
    //    UE_LOG(LogTemp, Warning, TEXT("Mesh destroyed!"));
    //}

    // Destroy the bullet after hit
    Destroy();
}

void ABullet::OwnerCollisionPrevention()
{
    AActor* Shooter = GetOwner();
    if (Shooter) {
        if (BulletMesh) {
            // Ignore collisions with the actor that shot the bullet
            BulletMesh->IgnoreActorWhenMoving(Shooter, true);
        }
    }
}
