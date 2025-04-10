#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrazierClass.generated.h"

class AGameManagerClass;

UCLASS()
class ARENAFPS_API ABrazierClass : public AActor
{
	GENERATED_BODY()

public:
	ABrazierClass();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "V0 var")
	UStaticMeshComponent* fireMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "V0 var")
	UMaterialInterface* blueMaterial;
	UMaterialInterface* baseMaterial;

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
	TArray<AActor*> EnemyArray;

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
