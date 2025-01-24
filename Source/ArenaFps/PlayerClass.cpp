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
#include "Components/Image.h"
#include "DrawDebugHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

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
				PlayerWidgetRef->RedScreen->SetOpacity(0.0f);
			}
		}
	}

	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(HandMaterial, this);

	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	for (UStaticMeshComponent* Component : Components)
	{
		if (Component->ComponentHasTag("Sphere1"))
		{
			sphere1 = Component;
		}
		else if (Component->ComponentHasTag("Sphere2"))
		{
			sphere2 = Component;
		}
		else if (Component->ComponentHasTag("LeftArm"))
		{
			Component->SetMaterial(0, DynamicMaterialInstance);
		}
		else if (Component->ComponentHasTag("RightArm"))
		{
			Component->SetMaterial(0, DynamicMaterialInstance);
		}
	}

	CameraComponent = FindComponentByClass<UCameraComponent>();
	firstWeaponCurrentAmmo = firstWeaponMaxAmmo;

	AddTimer(); //Start counting timer til the end
	RegenFunction();
}

// Called every frame
void APlayerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timeSinceLastShot += DeltaTime;

}

void APlayerClass::RegenFunction()
{
	currentHealth = FMath::Clamp((currentHealth + healthRegenAmount * 0.2), 0.0f, maxHealth);
	
	//if (timeSinceLastShot > 0.5)
	if (firstWeaponCurrentAmmo >= 10)
	{
		firstWeaponCurrentAmmo = FMath::Clamp((firstWeaponCurrentAmmo + firstWeaponAmmoRegenAmount * 0.2), 0.0f, firstWeaponMaxAmmo);
		PlayerWidgetRef->ChangeOverHeatProgress(firstWeaponCurrentAmmo / firstWeaponMaxAmmo);
	}


	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerClass::RegenFunction, 0.2f, false);
}

void APlayerClass::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	MovementVector = Value.Get<FVector2D>();

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
	if (canDash)
	{
		PlayerWidgetRef->DisplaySpeedOnDash();
		canDash = !canDash;

		FTimerHandle TimerHandleAuto;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleAuto, [this]()
			{
				canDash = !canDash;
			}, 1.0f, false);
	}
	
}
//
//void APlayerClass::ReloadFirstWeaponBlueprint()
//{
//
//}

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
		if (currentWeapon == 0)
		{
			if (firstWeaponCurrentAmmo >= 10 && canShootAgainFirstWeapon)
			{
				FVector CameraForwardVector = CameraComponent->GetForwardVector();
				FVector CameraLocation = CameraComponent->GetComponentLocation();

				FVector LaunchPosition;
				if (shootSphere1)
				{
					LaunchPosition = sphere1->GetComponentLocation();
					AnimateLeftHand();
				}
				else
				{
					LaunchPosition = sphere2->GetComponentLocation();
					AnimateRightHand();
				}
				shootSphere1 = !shootSphere1;

				DynamicMaterialInstance->SetScalarParameterValue(FName("HandColorParam"), (firstWeaponCurrentAmmo / firstWeaponMaxAmmo));

				AttackFireProjectile(LaunchPosition, FRotator(0, 0, 0));

				canShootAgainFirstWeapon = false;
				timeSinceLastShot = 0.0f;

				FTimerHandle TimerHandleAuto;
				GetWorld()->GetTimerManager().SetTimer(TimerHandleAuto, [this]()
					{
						canShootAgainFirstWeapon = true;
					}, delayBetweenFirstWeaponShot, false);

				firstWeaponCurrentAmmo -= 10;
				PlayerWidgetRef->ChangeOverHeatProgress(firstWeaponCurrentAmmo / firstWeaponMaxAmmo);
				if (firstWeaponCurrentAmmo < 10)
				{
					ReloadFirstWeaponBlueprint();

					UGameplayStatics::PlaySound2D(GetWorld(), OnOverheat);

					FTimerHandle TimerHandle;
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
						{
							firstWeaponCurrentAmmo = firstWeaponMaxAmmo;
							DynamicMaterialInstance->SetScalarParameterValue(FName("HandColorParam"), (firstWeaponCurrentAmmo / firstWeaponMaxAmmo));
							PlayerWidgetRef->ChangeOverHeatProgress(firstWeaponCurrentAmmo / firstWeaponMaxAmmo);
						}, 1.5, false);
				}

			}
		}
		
		else if (currentWeapon == 1)
		{

			UE_LOG(LogTemp, Warning, TEXT("Attacked with wep 1"));
		}
	}
}

void APlayerClass::AttackFireProjectile(FVector spawnPosition, FRotator spawnRotation)
{
	//Spawn du projectile

	int RandomNumber = FMath::RandRange(0, 2);
	if (RandomNumber == 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FireBall1);
	}
	else if (RandomNumber == 1)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FireBall2);
	}
	else if (RandomNumber == 2)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FireBall3);
	}

	FVector Direction = ReturnSightTargetLocation() - spawnPosition;
	Direction.Normalize();

	spawnPosition = spawnPosition - Direction * 500;


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

	//FVector SphereLocation = spawnPosition; // Exemple de position
	//float SphereRadius = 50.0f; // Rayon de la sph鑽e
	//int32 Segments = 12; // Complexit・de la sph鑽e
	//FColor SphereColor = FColor::Red; // Couleur de la sph鑽e
	//float Duration = 10.0f; // Dur馥 d'affichage en secondes
	//bool bPersistentLines = true; // Si vrai, la sph鑽e reste visible apr鑚 Duration si la console est ouverte
	//float LineThickness = 0.5; // ﾉpaisseur des lignes de la sph鑽e

	//DrawDebugSphere(GetWorld(), SphereLocation, SphereRadius, Segments, SphereColor, bPersistentLines, Duration, 0, LineThickness);

	ProjectileRef->ProjectileDirection = Direction;
}

void APlayerClass::AttackSpawnSpike(FVector spawnPosition, FRotator spawnRotation)
{

	////Spawn du spike
	//if (spikeRef)
	//{
	//	spikeRef->Destroy();
	//}
	//spawnRotation = FRotator(0.0f, spawnRotation.Yaw, 0.0f);
	//spawnPosition = GetActorLocation();
	//spawnPosition = GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	//spikeRef = GetWorld()->SpawnActor<AActor>(SpikeClass, spawnPosition, spawnRotation);
}

void APlayerClass::ChangeHealth(int amount)
{
	currentHealth += amount;
	PlayerWidgetRef->ChangeProgressBarFill(currentHealth / maxHealth);
	UE_LOG(LogTemp, Warning, TEXT("New health : %f"), currentHealth);

	if (amount < 0)
	{
		int RandomNumber = FMath::RandRange(0, 1);
		if (RandomNumber == 0)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), PlayerHit1);
		}
		else if (RandomNumber == 1)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), PlayerHit2);
		}
		PlayerWidgetRef->TurnScreenRed();
	}

	if (currentHealth <= 0)
	{
		//Destroy();
		PlayerWidgetRef->RemoveFromParent();

		GameOverWidgetRef = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		if (GameOverWidgetRef)
		{
			GameOverWidgetRef->AddToViewport();

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				PC->SetPause(true);

				// Assurez-vous que l'UI peut toujours recevoir des entr馥s
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(GameOverWidgetRef->TakeWidget());
				PC->SetInputMode(InputMode);

				PC->bEnableClickEvents = true;
				PC->bEnableMouseOverEvents = true;
				PC->bEnableTouchEvents = true;

				// Activer le curseur si n馗essaire
				PC->bShowMouseCursor = true;
			}
		}

	}
}

FVector APlayerClass::ReturnSightTargetLocation()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	FVector EndPoint = CameraLocation + CameraRotation.Vector() * 2000;
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndPoint, ECC_Visibility, QueryParams))
	{
		if (HitResult.bBlockingHit)
		{
			EndPoint = HitResult.Location; // Si un objet est touch・ utiliser ce point
		}
	}

	return EndPoint;
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
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerClass::Attack);

		//Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerClass::Dash);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No EIC found"));
	}
}

void APlayerClass::AddTimer()
{
	timeSinceStart += 1;
	int Minutes = timeSinceStart / 60;
	int Seconds = timeSinceStart % 60;

	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	PlayerWidgetRef->TimerTextBlock->SetText(FText::FromString(TimeString));

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerClass::AddTimer, 1.0f, false);
}