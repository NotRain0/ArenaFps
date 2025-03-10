// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerClass.h"

#include "BaseEnemy.h"
#include "BrazierClass.h"

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
}

// Called every frame
void ASpawnerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
