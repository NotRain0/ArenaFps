// Fill out your copyright notice in the Description page of Project Settings.


#include "StatManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UStatManagerComponent::UStatManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStatManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	ConfigStats();
}

void UStatManagerComponent::ChangeHealth(float amount)
{
	currentHealth += amount;
}

void UStatManagerComponent::ConfigStats()
{
	currentHealth = maxHealth;
	currentSpeed = baseSpeed;

	UE_LOG(LogTemp, Warning, TEXT("Finished configurating stats"));
}