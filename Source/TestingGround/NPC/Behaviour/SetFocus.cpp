// Fill out your copyright notice in the Description page of Project Settings.


#include "SetFocus.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "Engine/World.h"

EBTNodeResult::Type USetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    //AActor* FocusActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    //BlackboardComp->SetValueAsObject(FocusActorKey.SelectedKeyName, FocusActor);
    
    AActor* FocusActor = Cast<AActor>(BlackboardComp->GetValueAsObject(FocusActorKey.SelectedKeyName));
    
    OwnerComp.GetAIOwner()->K2_SetFocus(FocusActor);
    
    return EBTNodeResult::Succeeded;
}
