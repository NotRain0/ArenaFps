// Fill out your copyright notice in the Description page of Project Settings.


#include "ReworkedEnemBase.h"

// Sets default values
AReworkedEnemBase::AReworkedEnemBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReworkedEnemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReworkedEnemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AReworkedEnemBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

