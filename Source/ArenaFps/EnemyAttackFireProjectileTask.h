#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyAttackFireProjectileTask.generated.h"

/**
 * Custom Behavior Tree Task for enemy to fire a projectile.
 */
UCLASS()
class ARENAFPS_API UEnemyAttackFireProjectileTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UEnemyAttackFireProjectileTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class ABaseProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetLocationKey;
};