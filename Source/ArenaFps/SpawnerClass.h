// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerClass.generated.h"

class ABrazierClass;
class ABaseEnemy;

UCLASS()
class ARENAFPS_API ASpawnerClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemies();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TSubclassOf<ABaseEnemy> EnemyToSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	TArray<ABrazierClass*> BrazierArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int amountFirstWave = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
	int amountDelta = 5;

};
