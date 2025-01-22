// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"


UCLASS()
class ARENAFPS_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Var")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Var")
	float ProjectileDamage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Var")
	float HeadShotDamageMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Var")
	float ProjectileSpeed = 1500.0f;

	UPROPERTY(EditAnywhere, Category = "Var")
	int timeBeforeSelfDestruct = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Var")
	FVector ProjectileDirection;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void DestroyProjectile();
};
