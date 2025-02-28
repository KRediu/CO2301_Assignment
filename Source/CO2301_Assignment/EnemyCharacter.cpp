// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Bullet.h"
#include "Gun.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy Character Mesh"));
	EnemyMesh->SetupAttachment(RootComponent);

	EnemyBulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet"));
	EnemyBulletSpawnPoint->SetupAttachment(EnemyMesh);
	EnemyBulletSpawnPoint->SetRelativeLocation(FVector(60.0f, 20.0f, 24.0f));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	if (Gun) {
		Gun->AttachToEnemy(this);
		Gun->SetActorEnableCollision(false);
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::Fire() {
	if (BulletClass && !IsDead) { //checks bullet projectile has been set in the editor
		FVector SpawnLocation = EnemyBulletSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = EnemyBulletSpawnPoint->GetComponentRotation();
		ABullet* TempEnemyBullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation);

		TempEnemyBullet->SetOwner(this);
		TempEnemyBullet->OwnerCollisionPrevention();
		TempEnemyBullet->SetActorRelativeScale3D(FVector(0.075f, 0.075f, 0.075f));

		/*UGameplayStatics::PlaySound2D(GetWorld(), thunk);*/
	}
}

float AEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsDead) {
		UE_LOG(LogTemp, Warning, TEXT("Damage to enemy: %f"), DamageAmount);

		Health -= DamageAmount;
		if (Health <= 0)
			AEnemyCharacter::Death();

		return DamageAmount;
	}
	return 0;
}

void AEnemyCharacter::Death() 
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy slain"));
	IsDead = true;
	GetWorld()->GetTimerManager().SetTimer(DespawnTimer, this, &AEnemyCharacter::Despawn, 15.0f);
}

void AEnemyCharacter::Despawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy despawned"));
	EnemyMesh->SetAnimInstanceClass(nullptr);
	Destroy();
	Gun->Destroy();
}