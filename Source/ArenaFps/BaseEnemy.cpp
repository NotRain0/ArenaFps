// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"


ABaseEnemy::ABaseEnemy() // constructeur de l'enfant
{

	//bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")); // VO STUFF
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	bodyMesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));

	baseMaterial = bodyMesh->GetMaterial(0);
	currentMaterial = baseMaterial; // V0 STUFF

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnOverlapBegin);
	CapsuleComponent->SetSimulatePhysics(false);
}

void ABaseEnemy::ChangeHealth(int amount)
{
	currentHealth += amount;
	UE_LOG(LogTemp, Warning, TEXT("New health : %f"), currentHealth);

	if (currentHealth <= 0)
	{
		Destroy();
	}
	ChangeMaterial();
}

void ABaseEnemy::ChangeMaterial()
{
	if (!bodyMesh)
	{
		return;
	}

	if (currentMaterial == redMaterial)
	{
		currentMaterial = baseMaterial;
		bodyMesh->SetMaterial(0, baseMaterial);

	}
	else
	{
		currentMaterial = redMaterial;
		bodyMesh->SetMaterial(0, redMaterial);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseEnemy::ChangeMaterial, 0.25, false);
	}
}

void ABaseEnemy::Attack()
{

}

// En théorie c'est l'attaque qui devrait changer la vie, mais pour la V0 je fais ca comme ca, on changera après

void ABaseEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!OtherActor || OtherActor == this)
{
		return;
	}

	if (OtherActor && OtherActor->ActorHasTag(FName("FriendlyProjectile")))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s detected overlap with projectile"), *GetName());
	}

	else if (OtherActor && OtherActor->ActorHasTag(FName("FriendlySpike")))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s detected overlap spike"), *GetName());
		if (!ActorsArray.Contains(OtherActor))
		{
			ChangeHealth(-50);
			CapsuleComponent->SetSimulatePhysics(true);
			GetCapsuleComponent()->AddImpulse(FVector(0, 0, 1) * 1000.0f, NAME_None, true);

			UE_LOG(LogTemp, Warning, TEXT("Did get hit"));

			ActorsArray.Add(OtherActor); //Oui on le retire pas mais osef, V0

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
				{
					CapsuleComponent->SetSimulatePhysics(false);
				}, 1.0f, false);
		}
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s OnOverlapBegin with %s"), *GetName(), *OtherActor->GetName());
	}
}