// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerClass.h"
///
//
#include "EnhancedInputSubsystems.h"

void APlayerControllerClass::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

	}
}