#include "EnemyAttackFireProjectileTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.h"

UEnemyAttackFireProjectileTask::UEnemyAttackFireProjectileTask()
{
    NodeName = "Attack Fire Projectile";
}

EBTNodeResult::Type UEnemyAttackFireProjectileTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        UE_LOG(LogTemp, Error, TEXT("AIController is null!"));
        return EBTNodeResult::Failed;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("AIPawn is null!"));
        return EBTNodeResult::Failed;
    }


    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        UE_LOG(LogTemp, Error, TEXT("BlackboardComponent is null!"));
        return EBTNodeResult::Failed;
    }

    FVector TargetLocation = BlackboardComp->GetValueAsVector(TargetLocationKey.SelectedKeyName);

    FVector SpawnPosition = AIPawn->GetActorLocation();
    FRotator SpawnRotation = (TargetLocation - SpawnPosition).Rotation();

    FVector Direction = TargetLocation - SpawnPosition;
    Direction.Normalize();

    SpawnPosition -= Direction * 500.0f; 

    if (!ProjectileClass)
    {
        UE_LOG(LogTemp, Error, TEXT("ProjectileClass is null!"));
        return EBTNodeResult::Failed;
    }
    
    ABaseProjectile* ProjectileRef = AIPawn->GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, SpawnPosition, SpawnRotation);
    if (!ProjectileRef)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn projectile!"));
        return EBTNodeResult::Failed;
    }
    
    ProjectileRef->ProjectileDirection = Direction;

    return EBTNodeResult::Succeeded;
}
