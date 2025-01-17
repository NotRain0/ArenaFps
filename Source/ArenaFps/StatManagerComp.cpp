// Fill out your copyright notice in the Description page of Project Settings.


#include "StatManagerComp.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

UStatManagerComp::UStatManagerComp()
{
	PrimaryComponentTick.bCanEverTick = false;

	// On s'assure que le composant génère des overlaps
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionObjectType(ECC_WorldDynamic);
	SetCollisionResponseToAllChannels(ECR_Ignore);
	// Exemple : on overlap les Pions (Player, AI, etc.)
	SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// On bind la fonction de callback quand un overlap commence
	OnComponentBeginOverlap.AddDynamic(this, &UStatManagerComp::OnOverlapBegin);
}

void UStatManagerComp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Assurer qu’on ne traite pas l’Actor qui possède ce composant
    if (!OtherActor || OtherActor == GetOwner())
    {
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin with %s"), *OtherActor->GetName());
}

void UStatManagerComp::BeginPlay()
{
	Super::BeginPlay();

	ConfigStats();
}

void UStatManagerComp::ChangeHealth(float amount)
{
	currentHealth += amount;
}

void UStatManagerComp::ConfigStats()
{
	currentHealth = maxHealth;
	currentSpeed = baseSpeed;

	UE_LOG(LogTemp, Warning, TEXT("Finished configurating stats"));
}

