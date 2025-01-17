// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomCharacterClass.generated.h"

class UStaticMeshComponent;

UCLASS()
class ARENAFPS_API ACustomCharacterClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomCharacterClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	void ChangeHealth();

	void ChangeMaterial();

	int Health = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Var")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Var")
	UMaterialInterface* BaseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Var")
	UMaterialInterface* RedMaterial;

	UMaterialInterface* currentMaterial;

};
