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

public:
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

