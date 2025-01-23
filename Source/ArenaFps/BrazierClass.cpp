// Fill out your copyright notice in the Description page of Project Settings.


#include "BrazierClass.h"

#include "Components/BoxComponent.h"
#include "BaseEnemy.h"
#include "PlayerClass.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABrazierClass::ABrazierClass()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABrazierClass::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = Cast<UBoxComponent>(GetComponentByClass(UBoxComponent::StaticClass()));

	if (CollisionBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got collision box"));
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABrazierClass::OnOverlapBegin);
		CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABrazierClass::OnOverlapEnd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("no got collision box"));
	}

	currentHealth = maxHealth;

	fireMesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	baseMaterial = fireMesh->GetMaterial(0);

	LowerFireHealth();
}

// Called every frame
void ABrazierClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrazierClass::LowerFireHealth()
{
	if (!isImmune)
	{
		currentHealth -= EnemyDamageToFire * EnemyArray.Num() * 0.2; //toutes les 0.2sec c'est appelé, soit 5x par sec, largement assez pour ce genre d'interraction et low dmg
		if (currentHealth <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fire died"));
			DestroyFire();
		}
	}

	if (EnemyArray.Num() == 0)
	{	
		if (isPlayerInRange)
		{
			currentHealth = FMath::Clamp((currentHealth + FireRegenNearPlayer * 0.2), 0.0f, maxHealth);
		}
		else
		{
			currentHealth = FMath::Clamp((currentHealth + FireRegen * 0.2), 0.0f, maxHealth);
			//UE_LOG(LogTemp, Warning, TEXT("I applied regen, now health is : %f"), currentHealth);
		}
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABrazierClass::LowerFireHealth, 0.20, false); //recursif
}

void ABrazierClass::ImmuneFireToDamage()
{

	if (isImmune) //On stop l'immunité
	{
		UE_LOG(LogTemp, Error, TEXT("Fire immune is now over"));
		fireMesh->SetMaterial(0, baseMaterial);
		killCount = 0;
		killForImmune += killForImmuneDelta;
		immuneDuration += immuneDurationDelta;
	}

	else //On passe immune et tue tout l'monde
	{
		UE_LOG(LogTemp, Error, TEXT("Fire fed, now is immune"));
		fireMesh->SetMaterial(0, blueMaterial);
		
		TArray<ABaseEnemy*> EnemyArrayCopy = EnemyArray;
		for (ABaseEnemy* enemRef : EnemyArrayCopy)
		{
			if (enemRef) 
			{
				enemRef->ChangeHealth(-9999);
			}
		}

		KillEnemyInRangeBlueprintVisual();

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABrazierClass::ImmuneFireToDamage, immuneDuration, false);
	}

	isImmune = !isImmune;
}

void ABrazierClass::DestroyFire()
{
	UGameplayStatics::PlaySound2D(GetWorld(), OnDestroyedSound);
	Destroy();
}

void ABrazierClass::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
	{
		return;
	}

	if (OtherActor->ActorHasTag("EnemyTag") && !EnemyArray.Contains(OtherActor))
	{
		ABaseEnemy* EnemyRef = Cast<ABaseEnemy>(OtherActor);
		EnemyArray.Add(EnemyRef);
	}
	else if (OtherActor->ActorHasTag("PlayerTag"))
	{
		isPlayerInRange = true;
		UE_LOG(LogTemp, Warning, TEXT("Player entered fire range"));
	}
}

void ABrazierClass::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor)
	{
		return;
	}

	if (OtherActor->ActorHasTag("EnemyTag") && EnemyArray.Contains(OtherActor))
	{
		ABaseEnemy* EnemyRef = Cast<ABaseEnemy>(OtherActor);
		EnemyArray.Remove(EnemyRef);

		if (EnemyRef && EnemyRef->currentHealth <= 0)
		{
			//it died within fire range
			killCount += 1;
			if (killCount == killForImmune)
			{
				ImmuneFireToDamage();
			}
		}
	}
	else if (OtherActor->ActorHasTag("PlayerTag"))
	{
		isPlayerInRange = false;
		UE_LOG(LogTemp, Warning, TEXT("Player left fire range"));
	}
}