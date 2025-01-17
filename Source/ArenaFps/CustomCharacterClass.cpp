// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterClass.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ACustomCharacterClass::ACustomCharacterClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TempMesh"));
}

// Called when the game starts or when spawned
void ACustomCharacterClass::BeginPlay()
{
	Super::BeginPlay();

	BodyMesh = FindComponentByClass<UStaticMeshComponent>();
	currentMaterial = BaseMaterial;
}

void ACustomCharacterClass::ChangeHealth()
{
	Health -= 10;
	UE_LOG(LogTemp, Warning, TEXT("New health : %d"), Health);

	if (Health == 0)
	{
		Destroy();
	}
	ChangeMaterial();
}

void ACustomCharacterClass::ChangeMaterial()
{
	if (!BodyMesh)
	{
		return;
	}

	if (currentMaterial == RedMaterial)
	{
		currentMaterial = BaseMaterial;
		BodyMesh->SetMaterial(0, BaseMaterial);

	}
	else
	{
		currentMaterial = RedMaterial;
		BodyMesh->SetMaterial(0, RedMaterial);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ACustomCharacterClass::ChangeMaterial, 0.15, false);
	}
}

// Called every frame
void ACustomCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomCharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}