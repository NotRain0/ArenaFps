// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomCharacterClass.generated.h"


class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class ARENAFPS_API ACustomCharacterClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomCharacterClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame 
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public : //ref

	UCapsuleComponent* CapsuleComponent;


public:
	// Stats 

// Misc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	bool isFriendly;
	bool isStunned = false;
	bool canMove = true;

	void ConfigStats();

// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float maxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float currentHealth;

	UFUNCTION(BlueprintCallable, Category = "Character Stat")
	virtual void ChangeHealth(int Amount);
	virtual void CustomDeath();

// Attack
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	bool canAttack = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	bool isAttacking = false;

// Speed

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	//float baseSpeed;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	//float currentSpeed;

};
