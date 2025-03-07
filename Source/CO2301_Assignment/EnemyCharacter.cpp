// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "CO2301_AssignmentGameModeBase.h"
#include "Bullet.h"
#include "Gun.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// create enemy mesh
	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy Character Mesh"));
	EnemyMesh->SetupAttachment(RootComponent);

	// create enemy bullet spawnpoint
	EnemyBulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet"));
	EnemyBulletSpawnPoint->SetupAttachment(EnemyMesh);
	EnemyBulletSpawnPoint->SetRelativeLocation(FVector(60.0f, 20.0f, 24.0f));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// spawn gun actor
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	// attach to enemy and disable collisions with it
	Gun->AttachToEnemy(this);
	Gun->SetActorEnableCollision(false);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// firing function
void AEnemyCharacter::Fire() {
	if (BulletClass && !GameEnd) { // works if game is not finished
		FVector SpawnLocation = EnemyBulletSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = EnemyBulletSpawnPoint->GetComponentRotation();
		ABullet* TempEnemyBullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation); // spawn bullet by making a subclass

		TempEnemyBullet->SetOwner(this);
		TempEnemyBullet->OwnerCollisionPrevention(); // used to prevent collision with nmoving owner
		TempEnemyBullet->SetActorRelativeScale3D(FVector(0.075f, 0.075f, 0.075f)); // shrink to proper size

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), shootSound, GetActorLocation()); // play shooting sound
	}
}

float AEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser) // function for damage to actor
{
	if (!GameEnd) { // applies if game is not finished
		UE_LOG(LogTemp, Warning, TEXT("Damage to enemy: %f"), DamageAmount);

		Health -= DamageAmount; // remove damage from health
		if (Health <= 0) // death
		{
			AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
			AIController->GameFinish(); // call function in controller class to stop behavior tree

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), deathSound, GetActorLocation()); // play death sound

			WinReason = EWinReason::EnemyDeath; // set win reason
			AEnemyCharacter::Death(); 
		}

		return DamageAmount;
	}
	return 0;
}

void AEnemyCharacter::Death() // death function
{
	GameEnd = true; // set bool to prevent other functions from running

	ACO2301_AssignmentGameModeBase* GameMode = Cast<ACO2301_AssignmentGameModeBase>(UGameplayStatics::GetGameMode(this)); // pauses end timer to prevent other actions upon loss

	GameMode->GameOver(true); // call game end function
	GetWorld()->GetTimerManager().SetTimer(DespawnTimer, this, &AEnemyCharacter::Despawn, 15.0f); // call despawn timer for actor
}

void AEnemyCharacter::Despawn() // despawn function
{
	EnemyMesh->SetAnimInstanceClass(nullptr); // clear animation instance to prevent flooding error messages

	// destroy actor and attached gun actor
	Destroy(); 
	Gun->Destroy();
}