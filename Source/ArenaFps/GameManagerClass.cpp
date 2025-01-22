// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerClass.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

#include "SpawnerClass.h"
#include "BaseEnemy.h"
#include "BrazierClass.h"
#include "PlayerClass.h"

// Sets default values
AGameManagerClass::AGameManagerClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManagerClass::BeginPlay()
{
	Super::BeginPlay();
	
	for (TActorIterator<ABrazierClass> It(GetWorld()); It; ++It) //get brazier
	{
		ABrazierClass* brazierRef = *It;
		BrazierArray.Add(brazierRef);
	}

	for (TActorIterator<ASpawnerClass> It(GetWorld()); It; ++It) //
	{
		ASpawnerClass* spawnerRef = *It;
		SpawnerArray.Add(spawnerRef);
	}

	for (TActorIterator<APlayerClass> It(GetWorld()); It; ++It) //
	{
		playerRef = *It;
	}

	if (SpawnerArray.Num() > 0)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameManagerClass::StartSpawning, TimeBeforeFirstWave, false);
		UE_LOG(LogTemp, Error, TEXT("Will call wavespawn"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No valid spawner found, wave wont start"));
	}
}

// Called every frame
void AGameManagerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AGameManagerClass::StartSpawning()
{
	for (int i = 0; i < SpawnAmount; i++)
	{
		//ABaseProjectile* ProjectileRef = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, spawnPosition, spawnRotation);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameManagerClass::SpawnEnemy, i * 0.75, false);
		UE_LOG(LogTemp, Error, TEXT("Ordering to summon : %d"),i);
	}

	TimeBetweenWaves += TimeBetweenWavesDelta;
	SpawnAmount += SpawnAmountDelta;
	FTimerHandle TimerHandle2;
	GetWorldTimerManager().SetTimer(TimerHandle2, this, &AGameManagerClass::StartSpawning, TimeBetweenWaves, false);
}

void AGameManagerClass::SpawnEnemy()
{
	if (BrazierArray.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No brasier left"));
		return;
	}
	//TArray<ABrazierClass*> ValidBrazierArray = BrazierArray;

	///// Get valid fire
	//int fireTarget;
	//for (int i = 0; i < BrazierArray.Num(); i++)
	//{
	//	if (!BrazierArray[i]->isImmune)
	//	{
	//		ValidBrazierArray.Add(BrazierArray[i]);
	//	}
	//}
	//if (ValidBrazierArray.Num() == 0)
	//{
	//	fireTarget = 0;
	//}
	//else 
	//{
	//	fireTarget = FMath::RandRange(0, ValidBrazierArray.Num() - 1);
	//}

	//fireTarget = FMath::RandRange(0, ValidBrazierArray.Num() - 1);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Ignorer les collisions lors du spawn

	int spawnerIndex = FMath::RandRange(0, SpawnerArray.Num() - 1);

	ABaseEnemy* SpawnedActor = GetWorld()->SpawnActor<ABaseEnemy>(EnemyToSpawn, SpawnerArray[spawnerIndex]->GetActorLocation() , FRotator(0,0,0), SpawnParams);

	if (SpawnedActor)
	{
		float smallestDistance = FVector::Dist(SpawnedActor->GetActorLocation(), BrazierArray[0]->GetActorLocation());

		for (int i = 0; i < BrazierArray.Num(); i++)
		{
			float testDistance = FVector::Dist(SpawnedActor->GetActorLocation(), BrazierArray[i]->GetActorLocation());
			if (testDistance <= smallestDistance)
			{
				smallestDistance = testDistance;
				SpawnedActor->brazierTarget = BrazierArray[i];

				UE_LOG(LogTemp, Error, TEXT("Npc going to fire index : %d"), i);
			}
		}
		//SpawnedActor->brazierTarget = BrazierArray[FMath::RandRange(0, BrazierArray.Num() - 1)];
	}
}