// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageableComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINAL_API UDamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDamageableComponent();

	UFUNCTION()
	void ReceiveDamage(float Damage);

	UFUNCTION()
	void AddHealth(float Health);

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeathDelegate;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category=Setup)
	float MaxHealth = 100.f;

private:

	UPROPERTY()
	float CurrentHealth = 0.f;

		
};
