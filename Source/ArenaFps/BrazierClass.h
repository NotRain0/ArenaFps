// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrazierClass.generated.h"

class ABaseEnemy;
class AGameManagerClass;

UCLASS()
class ARENAFPS_API ABrazierClass : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABrazierClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: // Temporary, only for V0 purpose

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "V0 var")
	UStaticMeshComponent* fireMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "V0 var")
	UMaterialInterface* blueMaterial;
	UMaterialInterface* baseMaterial;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float maxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float EnemyDamageToFire = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float FireRegen = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float FireRegenNearPlayer = 5;

	/// <summary>
	/// Une fonction appelée toutes les 0.2 sec pour verifier et baisser la santé du brazier
	/// </summary>
	void LowerFireHealth();

	void ImmuneFireToDamage();

	

	bool isImmune = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float immuneDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float immuneDurationDelta = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float killForImmune;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float killForImmuneDelta = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	float killCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire Stat")
	TArray<ABaseEnemy*> EnemyArray;

	bool isPlayerInRange = false;

	void DestroyFire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void KillEnemyInRangeBlueprintVisual();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound ref")
	class USoundBase* OnDestroyedSound;

	AGameManagerClass* GameManagerRef;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};