// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FinalCharacter.generated.h"

UCLASS(config=Game)
class AFinalCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
public:
	
	AFinalCharacter();	

protected:
	
	void MoveForward(float Value);

	void MoveRight(float Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void AreaAttack();

	UFUNCTION()
	void RangeAttack();

	UFUNCTION()
	void OnAttackEnd();

	UPROPERTY()
	bool bIsAttacking;

	UPROPERTY(EditDefaultsOnly, Category = "Attacks Setup")
	float RangeAttackTime = 6.f;

	UPROPERTY(EditDefaultsOnly, Category = "Attacks Setup")
	float AreaAttackTime = 6.f;

	UPROPERTY()
	FTimerHandle AttackTimer;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	class USphereComponent* AreaAttackSphere;

	UPROPERTY(EditDefaultsOnly, Category="Attacks Setup")
	float AreaAttackDamage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category="Attacks Setup")
	TSubclassOf<class APlayerProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Attacks Setup")
	float RangeAttackDamage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	class USceneComponent* ProjectileSpawnPoint;
	
public:
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

