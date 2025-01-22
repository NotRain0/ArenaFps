// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "EnemyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ARENAFPS_API AEnemyProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
								 AActor* OtherActor, 
								 UPrimitiveComponent* OtherComp, 
								 int32 OtherBodyIndex, 
								 bool bFromSweep, 
								 const FHitResult& SweepResult) override;

	
};


