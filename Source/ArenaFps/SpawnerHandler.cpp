// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerHandler.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"

#include "SpawnerClass.h"
#include "ReworkedEnemBase.h"

// Sets default values
ASpawnerHandler::ASpawnerHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnerHandler::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ASpawnerClass> It(GetWorld()); It; ++It) //
	{
		ASpawnerClass* spawnerRef = *It;
		SpawnerArray.Add(spawnerRef);
	}

	if (SpawnerArray.Num() > 0)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnerHandler::StartSpawning, TimeBeforeFirstWave, false);
		UE_LOG(LogTemp, Error, TEXT("Spawners found, shall call first wave"));
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("No valid spawner found, wave wont start"));
	}
}

// Called every frame
void ASpawnerHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// La fonction regarde d'abord tous les enemies qu'elle va spawn : easter egg ou vague normale.
/// Elle va remplir une liste avec chaque enemie présent dans la vague, puis la shuffle pour le cote random.
/// On ordonne ensuite tous les spawns d'un coup, avec un ftimer : c'est pratique car le spawn n'a jamais a etre interrompu, donc pas besoin de referencer les ftimers.
void ASpawnerHandler::StartSpawning() 
{
	EnemyToSpawnList.Empty();
	SpawnIndex += 1;
	int i;

	UE_LOG(LogTemp, Error, TEXT("New wave started"));

	if (FMath::RandRange(1, SnakeWaveRange) == 1) // Easter egg / custom wave : all snake wave, but with less of them
	{
		for (i = 0; i < floor((SpiritAmount + SnakeAmount) / 3); i++)
		{
			EnemyToSpawnList.Add(SnakeClass);
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnerHandler::SpawnEnemy, i * 0.75, false);
		}
	}

	else
	{
		for (i = 0; i < SnakeAmount; i++)
		{
			EnemyToSpawnList.Add(SnakeClass);
		}
		for (i = 0; i < SpiritAmount; i++)
		{
			EnemyToSpawnList.Add(SpiritClass);
		}

		ShuffleArray(EnemyToSpawnList);

		for (i = 0; i < SnakeAmount + SpiritAmount; i++)
		{
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnerHandler::SpawnEnemy, i * 0.75, false); //Based sur i, donc spawn apres 0.75s, 1.5s, 2.25s, 3s, etc
		}
	}

	TimeBetweenWaves += TimeBetweenWavesDelta;
	SpiritAmount += SpiritAmountIncr;
	if (WaveIndex % SnakeIncrWaveDelay == 0) SnakeAmount += 1;

	FTimerHandle TimerHandle2;
	GetWorldTimerManager().SetTimer(TimerHandle2, this, &ASpawnerHandler::StartSpawning, TimeBetweenWaves, false); //Start waiting for the next wave
}

void ASpawnerHandler::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	int spawnerIndex = FMath::RandRange(0, SpawnerArray.Num() - 1); //le spawner auquel le npc apparait

	AActor* SpawnedEnemy = GetWorld()->SpawnActor<AActor>(EnemyToSpawnList[SpawnIndex], SpawnerArray[spawnerIndex]->GetActorLocation(), FRotator(0, 0, 0), SpawnParams);
	SpawnIndex += 1;
}

// Une copie de la fonction shuffle blueprint
void ASpawnerHandler::ShuffleArray(TArray<TSubclassOf<AActor>>& OutArray)
{
	if (OutArray.Num() > 1)
	{
		for (int32 i = 0; i < OutArray.Num(); i++)
		{
			const int32 j = FMath::RandRange(i, OutArray.Num() - 1);
			if (i != j)
			{
				OutArray.Swap(i, j);
			}
		}
	}
}