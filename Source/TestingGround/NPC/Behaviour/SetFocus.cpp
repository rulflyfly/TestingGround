// Fill out your copyright notice in the Description page of Project Settings.


#include "SetFocus.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    FVector FocusLocation = BlackboardComp->GetValueAsVector(FocusLocationKey.SelectedKeyName);
    
    OwnerComp.GetAIOwner()->K2_SetFocalPoint(FocusLocation);
    
    return EBTNodeResult::Succeeded;
}
