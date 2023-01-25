// Copyright Epic Games, Inc. All Rights Reserved.

#include "FinalCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

AFinalCharacter::AFinalCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;	
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 

}

void AFinalCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{	
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("RangeAttack", IE_Pressed, this, &AFinalCharacter::RangeAttack);
	
	PlayerInputComponent->BindAction("AreaAttack", IE_Pressed, this, &AFinalCharacter::AreaAttack);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFinalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFinalCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AFinalCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFinalCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AFinalCharacter::AreaAttack()
{
	if(bIsAttacking) return;
	bIsAttacking = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("AreaAttack"));
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AFinalCharacter::OnAttackEnd, AreaAttackTime, false);
}

void AFinalCharacter::RangeAttack()
{
	if(bIsAttacking) return;
	bIsAttacking = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("RangeAttack"));
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AFinalCharacter::OnAttackEnd, RangeAttackTime, false);
}

void AFinalCharacter::OnAttackEnd()
{
	bIsAttacking = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("EndAttack"));
}
