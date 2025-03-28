// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GetTarget.h"

#include "EngineUtils.h" //TActorIterator 
#include "PlayerClass.h"
#include "BrazierClass.h"

EBTNodeResult::Type UBTT_GetTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //Super::ExecuteTask(OwnerComp, NodeMemory);

    if (TagToFind == "PlayerTag")
    {
        for (TActorIterator<APlayerClass> ActorItr(GetWorld()); ActorItr; ++ActorItr)
        {
            APlayerClass* ActorFound = *ActorItr;
            if (ActorFound && ActorFound->Tags.Contains(TagToFind))
            {
                //AActor* TargetRef = Cast<AActor>(ActorFound);
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, ActorFound);
                return EBTNodeResult::Succeeded;
            }
        }
    }
    else if (TagToFind == "BrazierTag")
    {
        for (TActorIterator<ABrazierClass> ActorItr(GetWorld()); ActorItr; ++ActorItr)
        {
            ABrazierClass* ActorFound = *ActorItr;
            if (ActorFound && ActorFound->Tags.Contains(TagToFind))
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, ActorFound);
                return EBTNodeResult::Succeeded;
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Didnt find player"));
    return EBTNodeResult::Failed;
}