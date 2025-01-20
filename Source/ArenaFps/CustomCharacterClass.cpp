// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterClass.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ACustomCharacterClass::ACustomCharacterClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomCharacterClass::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent = GetCapsuleComponent();
	ConfigStats();
}

// Called every frame
void ACustomCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomCharacterClass::ConfigStats()
{
	currentHealth = maxHealth;
	//currentSpeed = baseSpeed;

	UE_LOG(LogTemp, Warning, TEXT("Finished configurating stats"));
}
void ACustomCharacterClass::ChangeHealth(int amount)
{
	currentHealth += amount;
	UE_LOG(LogTemp, Warning, TEXT("New health : %f"), currentHealth);

	if (currentHealth == 0)
	{
		CustomDeath();
	}

	else if (currentHealth > maxHealth)
	{
		currentHealth = maxHealth;
	}
	//ChangeMaterial();
}

void ACustomCharacterClass::CustomDeath()
{
	Destroy();
}

// Called to bind functionality to input
void ACustomCharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomCharacterClass::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}