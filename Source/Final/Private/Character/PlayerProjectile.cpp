// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerProjectile.h"

#include "Components/DamageableComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

APlayerProjectile::APlayerProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	SetRootComponent(ProjectileMesh);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(GetRootComponent());

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void APlayerProjectile::InitializeProjectile(float NewDamage, AActor* NewOwner)
{
	Damage = NewDamage;
	ProjectileOwner = NewOwner;
	CollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &APlayerProjectile::OnOverlapBegin);
}

void APlayerProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == ProjectileOwner)
	{
		return;
	}
	
	if(UDamageableComponent* DamageableComponent = OtherActor->FindComponentByClass<UDamageableComponent>())
	{
		DamageableComponent->ReceiveDamage(Damage);
	}
	Destroy();
}
