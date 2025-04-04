// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomCharacterClass.h"
#include "PlayerClass.generated.h"

//Inputs
class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class USoundBase;
//
class UPlayerWidget;
class ABaseProjectile;
class APlayerProjectile;

UCLASS()
class ARENAFPS_API APlayerClass : public ACustomCharacterClass
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public : 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Component")
	class UCameraComponent* CameraComponent;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Component")
	class UCharacterMovementComponent* MyCharMoveComponent;

public:

//Inputs 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ChangeWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Attack();

	void ChangeWeapon();

	void Dash();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AActor* ReturnSightTarget();

public : 

//ref

	//Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UPlayerWidget* PlayerWidgetRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UUserWidget* GameOverWidgetRef;


	//Projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Ref")
	TSubclassOf<ABaseProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Ref")
	TSubclassOf<APlayerProjectile> SecondWeaponProjectileClass;

	//Spike
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Ref")
	TSubclassOf<AActor> SpikeClass;
	AActor* spikeRef;

	UPROPERTY(BlueprintReadWrite)
	FVector2D MovementVector = FVector2D(0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Ref")
	UStaticMeshComponent* sphere1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Ref")
	UStaticMeshComponent* sphere2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Ref")
	class UMaterial* HandMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Ref")
	class UMaterialInstanceDynamic* DynamicMaterialInstance;

	bool shootSphere1 = true;

	int timeSinceStart = -1;
	void AddTimer();
	

public:
	// Stats 
	// 
	bool canDash = true; 
//Health
	virtual void ChangeHealth(int Amount);

	// Per Second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float healthRegenAmount;

	/// Weapons are 0 or 1 so far
	/// 0 is gun
	/// 1 is spike
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	int currentWeapon = 0;

	bool canChangeWeapon = true;

	void SpawnFireProjectile(FVector spawnPosition, FRotator spawnRotation);

	void AttackSpawnSpike(FVector spawnPosition, FRotator spawnRotation);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void ReloadFirstWeaponBlueprint();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void AnimateLeftHand();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void AnimateRightHand();

	bool canRegenAmmo = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float firstWeaponMaxAmmo = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float firstWeaponCurrentAmmo = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float firstWeaponAmmoRegenAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float delayBetweenFirstWeaponShot = 0.35;

	float timeSinceLastShot = 0.0f;
	bool canShootAgainFirstWeapon = true;

//////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float secondWeaponCooldown = 1.5f;

	bool canShootAgainSecondWeapon = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Ref")
	FVector SpawnOffsetSecondWeapon;

	APlayerProjectile* ExplosiveProjectileRef;

	void SpawnSecondWeaponProjectile();



	void RegenFunction();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	//float firstWeaponReloadTime = 1.5;

public: //Sounds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound ref")
	USoundBase* PlayerHit1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound ref")
	USoundBase* PlayerHit2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound ref")
	USoundBase* OnOverheat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound ref")
	USoundBase* FireBall1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound ref")
	USoundBase* FireBall2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound ref")
	USoundBase* FireBall3;

};

