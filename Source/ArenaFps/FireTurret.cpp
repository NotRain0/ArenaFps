// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTurret.h"

// Sets default values
AFireTurret::AFireTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFireTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

