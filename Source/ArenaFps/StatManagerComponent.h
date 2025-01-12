// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENAFPS_API UStatManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ConfigStats(); 
	
	void ChangeHealth(float amount);

public : 
	// Stats 

// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float maxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float currentHealth;

// Attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float attackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float baseAttackCooldown;

// Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float baseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float currentSpeed;

// Status

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status Info")
	bool isStunned = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status Info")
	bool isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status Info")
	bool canMove = true;
};
