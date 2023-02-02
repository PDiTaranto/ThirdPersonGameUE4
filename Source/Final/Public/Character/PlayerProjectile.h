// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.generated.h"

UCLASS()
class FINAL_API APlayerProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	float Damage = 0.f;

	UPROPERTY()
	AActor* ProjectileOwner = nullptr;
	
public:	
	APlayerProjectile();

	UFUNCTION()
	void InitializeProjectile(float NewDamage, AActor* NewOwner);

protected:
	
	UPROPERTY(EditDefaultsOnly, Category=Components)
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	class USphereComponent* CollisionSphere;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
