// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "EnemyCharacter.h"
#include "MyCharacter.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetSimulatePhysics(true);
	BulletMesh->SetNotifyRigidBodyCollision(true);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 10.0f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
	const FHitResult& Hit) {
	if (OtherActor->GetClass()->IsChildOf(AMyCharacter::StaticClass()) || OtherActor->GetClass()->IsChildOf(AEnemyCharacter::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("OnMyActorHit worked!"));
		AActor* ProjectileOwner = GetOwner();
		if (ProjectileOwner == NULL) {
			return;
		}
		UGameplayStatics::ApplyDamage(
			OtherActor, //actor that will be damaged
			10.0f, //the base damage to apply
			ProjectileOwner->GetInstigatorController(), //controller that caused the damage
			this, //Actor that actually caused the damage
			UDamageType::StaticClass() //class that describes the damage that was done
		);
		Destroy();
	}
}