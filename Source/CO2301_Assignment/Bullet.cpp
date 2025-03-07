#include "Bullet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

    // create bullet mesh and appropriate collision/physics
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(RootComponent);
    BulletMesh->SetSimulatePhysics(false); // Disable physics simulation - prevents bouncing and phasing through walls
	BulletMesh->SetNotifyRigidBodyCollision(true);
    BulletMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BulletMesh->SetCollisionResponseToAllChannels(ECR_Block); // Blocks all collisions

    // create projectile component
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
	
	OnActorHit.AddDynamic(this, &ABullet::OnHit); // apply delegate function on hit
}

void ABullet::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
	const FHitResult& Hit) { // damage actor on hit

    AActor* ProjectileOwner = GetOwner(); // get bullet owner

    // apply damage to all actors that support it
    UGameplayStatics::ApplyDamage(
        OtherActor,
        10.0f,
        ProjectileOwner->GetInstigatorController(),
        this,
        UDamageType::StaticClass()
    );

    // Check if actor is a character and apply impulse force
    ACharacter* HitCharacter = Cast<ACharacter>(OtherActor);
    FVector HitDirection = (HitCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    HitCharacter->GetCharacterMovement()->AddImpulse(HitDirection * 500.0f, true);

    Destroy(); // destroy bullet after damage application
}

// function that prevents collision of owner with bullet when fired while moving forward
void ABullet::OwnerCollisionPrevention()
{
    AActor* Shooter = GetOwner();
    BulletMesh->IgnoreActorWhenMoving(Shooter, true);
}
