// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class CO2301_ASSIGNMENT_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UFUNCTION()
	void OwnerCollisionPrevention();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BulletMesh;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 5000.0f;

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
		const FHitResult& Hit);
};
