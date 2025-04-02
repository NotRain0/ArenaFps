// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerHandler.generated.h"

class ASpawnerClass;
class AReworkedEnemBase;

UCLASS()
class ARENAFPS_API ASpawnerHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnerHandler();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TArray<ASpawnerClass*> SpawnerArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int TimeBeforeFirstWave = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int TimeBetweenWaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int TimeBetweenWavesDelta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int SpiritAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int SpiritAmountIncr; //pour incrementation, ++

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int SnakeAmount;

	// Tous les X tours, +1 snake
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int SnakeIncrWaveDelay = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int WaveIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TSubclassOf<AActor> SpiritClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TSubclassOf<AActor> SnakeClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TArray<TSubclassOf<AActor>> EnemyToSpawnList;

	int SpawnIndex = 0;

	// 1 / snakewavedivdedchance, ca fera un roll entre 0 et le chiffre -1 : 100 = 1% de chance, 1000 = 0.1%
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int SnakeWaveRange = 50;

	void StartSpawning();

	void SpawnEnemy();

	void ShuffleArray(TArray<TSubclassOf<AActor>>& OutArray); //copie de la fonction source
};
