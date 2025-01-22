// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManagerClass.generated.h"

class APlayerClass;
class ABaseEnemy;
class ASpawnerClass;
class ABrazierClass;

UCLASS()
class ARENAFPS_API AGameManagerClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManagerClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TArray<ABrazierClass*> BrazierArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TArray<ASpawnerClass*> SpawnerArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int TimeBeforeFirstWave = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int TimeBetweenWaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int TimeBetweenWavesDelta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int SpawnAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int SpawnAmountDelta;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int WaveIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TSubclassOf<ABaseEnemy> EnemyToSpawn;

	APlayerClass* playerRef;

	void StartSpawning();

	void SpawnEnemy();
};
