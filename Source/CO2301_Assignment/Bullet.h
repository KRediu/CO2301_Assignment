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

	// collision prevention func
	UFUNCTION()
	void OwnerCollisionPrevention();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// bullet mesh and movement
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BulletMesh;
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	// bullet speed
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 3000.0f;

	//hit function
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
		const FHitResult& Hit);
};
