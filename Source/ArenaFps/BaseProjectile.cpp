// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

#include "BaseEnemy.h"
//

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlapBegin);
	
	FTimerHandle TimerHandleRef; //Pour self destruct apres trop longtemps
	GetWorld()->GetTimerManager().SetTimer(TimerHandleRef, this, &ABaseProjectile::DestroyProjectile, timeBeforeSelfDestruct, false);
}

void ABaseProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile is overlapping"));
	if (OtherActor && OtherActor->ActorHasTag("EnemyTag"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile hit enemy"));
		
		ABaseEnemy* EnemyRef = Cast<ABaseEnemy>(OtherActor);
		if (EnemyRef)
		{
			EnemyRef->ChangeHealth(-20);
		}
		DestroyProjectile();
	}
}
//
void ABaseProjectile::DestroyProjectile()
{
	Destroy();
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (ProjectileDirection * ProjectileSpeed * DeltaTime);
	SetActorLocation(NewLocation);

}

