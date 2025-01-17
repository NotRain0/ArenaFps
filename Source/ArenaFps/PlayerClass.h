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

//
class UStatManagerComponent;
class UPlayerWidget;
class ABaseProjectile;

UCLASS()
class ARENAFPS_API APlayerClass : public ACustomCharacterClass
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public : 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Component")
	class UCameraComponent* CameraComponent;;

	UStatManagerComponent* statManager;

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

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public : 

	
//ref

	//Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UPlayerWidget* PlayerWidgetRef;

	//Projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Var")
	TSubclassOf<ABaseProjectile> ProjectileClass;
	


};

