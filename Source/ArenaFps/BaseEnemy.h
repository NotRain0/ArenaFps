// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomCharacterClass.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
class ABrazierClass;

class UStaticMeshComponent;

UCLASS()
class ARENAFPS_API ABaseEnemy : public ACustomCharacterClass
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public :

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public: // Stats 

	//Health
	virtual void ChangeHealth(int Amount);
	//virtual void CustomDeath();


// Attack

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float attackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float attackCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	float attackRange;
	virtual void Attack();


public: // Temporary, only for V0 purpose

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Ref")
	UStaticMeshComponent* bodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Ref")
	UMaterialInterface* redMaterial;
	UMaterialInterface* currentMaterial;
	UMaterialInterface* baseMaterial;

	void ChangeMaterial();

	TArray<AActor*> ActorsArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stat")
	ABrazierClass* brazierTarget;

	bool isBurning = false;
	
	void SetAblaze();

	//FTimer* BurningTimer;



};
