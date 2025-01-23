// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"

#include "PlayerClass.h"




void AEnemyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
                                      AActor* OtherActor, 
                                      UPrimitiveComponent* OtherComp, 
                                      int32 OtherBodyIndex, 
                                      bool bFromSweep, 
                                      const FHitResult& SweepResult)
{

	//UE_LOG(LogTemp, Warning, TEXT("Projectile is overlapping"));
	if (OtherActor && OtherActor->ActorHasTag("PlayerTag"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile hit enemy"));
		
		APlayerClass* PlayerRef = Cast<APlayerClass>(OtherActor);
		if (PlayerRef)
		{
			PlayerRef->ChangeHealth(-20);
		}
		DestroyProjectile();
	}
	if (OtherActor && OtherActor->ActorHasTag("Wall"))
	{
		DestroyProjectile();
	}



	
}
void AEnemyProjectile::OnHit(UPrimitiveComponent* HitComp, 
							AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, 
							FVector NormalImpulse, 
							const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile hit something: %s"), *OtherActor->GetName());
	
	DestroyProjectile(); 
}