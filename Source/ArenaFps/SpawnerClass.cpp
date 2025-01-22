// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerClass.h"

#include "BaseEnemy.h"
#include "BrazierClass.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"

// Sets default values
ASpawnerClass::ASpawnerClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnerClass::BeginPlay()
{
	Super::BeginPlay();
	
	//for (TActorIterator<ABrazierClass> It(GetWorld()); It; ++It)
	//{
	//	ABrazierClass* brazierRef = *It;
	//	BrazierArray.Add(brazierRef);
	//}
}

// Called every frame
void ASpawnerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerClass::SpawnEnemies()
{
	//spikeRef = GetWorld()->SpawnActor<AActor>(SpikeClass, spawnPosition, spawnRotation);

	int fireTarget  = FMath::RandRange(0, BrazierArray.Num()-1);
}
