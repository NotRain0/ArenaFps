// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerClass.h"
////
// Inputs
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "StatManagerComponent.h"

// //
#include "StatManagerComponent.h"


// Called when the game starts or when spawned
void APlayerClass::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Player BeginPlay"));

	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}

	statManager = Cast<UStatManagerComponent>(GetComponentByClass(UStatManagerComponent::StaticClass()));
}

void APlayerClass::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	//FTimerHandle TimerHandle;
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyCharacter::ResetWalkSoundBool, 0.3f, false);


	if (Controller != nullptr && statManager->canMove)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerClass::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerClass::Fire(const FInputActionValue& Value)
{
	if (!(statManager->isAttacking))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attacked"));
	}
}

// Called to bind functionality to input
void APlayerClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerClass::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerClass::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerClass::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerClass::Look);

		//Attack
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerClass::Fire);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No EIC found"));
	}
}