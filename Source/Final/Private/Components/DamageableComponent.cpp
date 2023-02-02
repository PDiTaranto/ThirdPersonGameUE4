// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageableComponent.h"

UDamageableComponent::UDamageableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDamageableComponent::ReceiveDamage(float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
	if(CurrentHealth <= 0.f)
	{
		OnDeathDelegate.Broadcast();
		DestroyComponent();
	}
}

void UDamageableComponent::AddHealth(float Health)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Health, 0.f, MaxHealth);
}

void UDamageableComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}
