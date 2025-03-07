#include "Gun.h"
#include "MyCharacter.h"
#include "EnemyCharacter.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = false;

	// gun setup
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Attachment"));
	GunMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::AttachToCharacter(AMyCharacter* Character) // attach to player
{
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachRules, TEXT("gun_socket")); // attach to gun_socket part
}

void AGun::AttachToEnemy(AEnemyCharacter* EnemyCharacter) // attach to enemy
{
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(EnemyCharacter->GetMesh(), AttachRules, TEXT("gun_socket")); // attach to gun_socket part
}
