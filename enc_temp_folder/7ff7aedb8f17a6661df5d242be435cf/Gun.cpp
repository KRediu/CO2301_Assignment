// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "MyCharacter.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Attachment"));
	GunMesh->SetupAttachment(RootComponent);


	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet"));
	BulletSpawnPoint->SetupAttachment(GunMesh);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::AttachToCharacter(AMyCharacter* Character)
{
	if (Character && Character->GetMesh())
	{
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(Character->GetMesh(), AttachRules, TEXT("gun_socket"));
	}
}