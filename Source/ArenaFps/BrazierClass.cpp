#include "BrazierClass.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameManagerClass.h"

ABrazierClass::ABrazierClass()
{
	PrimaryActorTick.bCanEverTick = true;
}

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
		UE_LOG(LogTemp, Warning, TEXT("No collision box found"));
	}

	currentHealth = maxHealth;

	fireMesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	baseMaterial = fireMesh->GetMaterial(0);

	LowerFireHealth();
}

void ABrazierClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrazierClass::LowerFireHealth()
{
	if (!isImmune)
	{
		currentHealth -= EnemyDamageToFire * EnemyArray.Num() * 0.2f;

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
			currentHealth = FMath::Clamp((currentHealth + FireRegenNearPlayer * 0.2f), 0.0f, maxHealth);
		}
		else
		{
			currentHealth = FMath::Clamp((currentHealth + FireRegen * 0.2f), 0.0f, maxHealth);
		}
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABrazierClass::LowerFireHealth, 0.2f, false);
}

void ABrazierClass::ImmuneFireToDamage()
{
	if (isImmune)
	{
		UE_LOG(LogTemp, Error, TEXT("Fire immune is now over"));
		fireMesh->SetMaterial(0, baseMaterial);
		killCount = 0;
		killForImmune += killForImmuneDelta;
		immuneDuration += immuneDurationDelta;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fire fed, now is immune"));
		fireMesh->SetMaterial(0, blueMaterial);

		TArray<AActor*> EnemyArrayCopy = EnemyArray;
		for (AActor* Enemy : EnemyArrayCopy)
		{
			if (Enemy && Enemy->ActorHasTag("BaseEnemyTag"))
			{
				// Optional: Use an interface or BlueprintCallable function here
				// Or you can Destroy() directly if it's enough
				Enemy->Destroy();
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
	if (GameManagerRef)
	{
		GameManagerRef->BrazierArray.Remove(this);
	}
	Destroy();
}

void ABrazierClass::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
	{
		return;
	}

	if (OtherActor->ActorHasTag("BaseEnemyTag") && !EnemyArray.Contains(OtherActor))
	{
		EnemyArray.Add(OtherActor);
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

	if (OtherActor->ActorHasTag("BaseEnemyTag") && EnemyArray.Contains(OtherActor))
	{
		EnemyArray.Remove(OtherActor);
		
		if ((OtherActor->ActorHasTag("BaseEnemyTag")))
		{
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
