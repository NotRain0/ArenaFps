// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerClass.h"
////
// Inputs
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "StatManagerComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// //
#include "PlayerWidget.h"
#include "BaseProjectile.h"


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

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (PlayerWidgetClass)
		{
			PlayerWidgetRef = CreateWidget<UPlayerWidget>(PC, PlayerWidgetClass);
			if (PlayerWidgetRef)
			{
				PlayerWidgetRef->AddToViewport();
			}
		}
	}

	CameraComponent = FindComponentByClass<UCameraComponent>();
}

void APlayerClass::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	//FTimerHandle TimerHandle;
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyCharacter::ResetWalkSoundBool, 0.3f, false);


	if (Controller != nullptr && canMove)
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

void APlayerClass::Dash()
{

}

void APlayerClass::ChangeWeapon()
{
	currentWeapon += 1;
	if (currentWeapon > 1) // en vrai on pourrait juste use une bool mais bon voyons grands
	{
		currentWeapon = 0;
	}
}

void APlayerClass::Attack()
{
	if (!isAttacking && canAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attacked"));

		
		FVector CameraForwardVector = CameraComponent->GetForwardVector();
		FVector CameraLocation = CameraComponent->GetComponentLocation();

		FVector LaunchPosition = CameraLocation + (CameraForwardVector * 50.0f); //Pour créer le projectile 0.5m devant soit
		FRotator ProjectileRotation = FRotationMatrix::MakeFromX(CameraForwardVector).Rotator();

		if (currentWeapon == 0)
		{
			AttackFireProjectile(LaunchPosition, ProjectileRotation);

		}
		
		else if (currentWeapon == 1)
		{

			AttackSpawnSpike(LaunchPosition, ProjectileRotation);
		}
	}
}

void APlayerClass::AttackFireProjectile(FVector spawnPosition, FRotator spawnRotation)
{
	//Spawn du projectile

	if (!ProjectileClass || !CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ProjectileClass or CameraComponent is null !!!"));
		return;
	}

	ABaseProjectile* ProjectileRef = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, spawnPosition, spawnRotation);
	if (!ProjectileRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Ref is null wtf !!!"));
		return;
	}
	ProjectileRef->ProjectileDirection = CameraComponent->GetForwardVector();
}

void APlayerClass::AttackSpawnSpike(FVector spawnPosition, FRotator spawnRotation)
{

	//Spawn du spike
	if (spikeRef)
	{
		spikeRef->Destroy();
	}
	spawnRotation = FRotator(0.0f, spawnRotation.Yaw, 0.0f);
	spawnPosition = GetActorLocation();
	spawnPosition = GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	spikeRef = GetWorld()->SpawnActor<AActor>(SpikeClass, spawnPosition, spawnRotation);
}

void APlayerClass::ChangeHealth(int amount)
{
	currentHealth += amount;
	PlayerWidgetRef->ChangeProgressBarFill(currentHealth / maxHealth);
	UE_LOG(LogTemp, Warning, TEXT("New health : %f"), currentHealth);

	if (amount < 0)
	{
		PlayerWidgetRef->TurnScreenRed();
	}

	if (currentHealth <= 0)
	{
		Destroy();
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

		//Change Weapon
		EnhancedInputComponent->BindAction(ChangeWeaponAction, ETriggerEvent::Started, this, &APlayerClass::ChangeWeapon);

		//Attack
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerClass::Attack);

		//Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerClass::Dash);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No EIC found"));
	}
}