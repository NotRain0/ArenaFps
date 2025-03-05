// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"

#include "BaseEnemy.h"
#include "TextActor.h"

//La partie "growth" dans le begin player, et le "launch" est dans le player class;

void APlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		FVector NewLocation = GetActorLocation() + (ProjectileDirection * ProjectileSpeed * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

void APlayerProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("EnemyTag"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap detected with %s"), *OtherComp->GetName());

		ABaseEnemy* EnemyRef = Cast<ABaseEnemy>(OtherActor);
		if (EnemyRef)
		{
			float damageToDisplay = 0;
			bool isHeadshot = false;

			EnemyRef->StartBurning();

			if (OtherComp->ComponentHasTag("BodyTag"))
			{
				EnemyRef->ChangeHealth(-ProjectileDamage);
				damageToDisplay = ProjectileDamage;


			}
			else if (OtherComp->ComponentHasTag("HeadTag"))
			{
				EnemyRef->ChangeHealth(-ProjectileDamage * HeadShotDamageMultiplier);
				damageToDisplay = ProjectileDamage * HeadShotDamageMultiplier;
				isHeadshot = true;
			}

			ATextActor* TextActorRef = GetWorld()->SpawnActor<ATextActor>(TextActorToSpawn, EnemyRef->GetActorLocation(), FRotator(0, 0, 0));
			if (TextActorRef)
			{
				TextActorRef->SetDamageText(damageToDisplay, isHeadshot);
			}
		}
		DestroyProjectile();
	}
}