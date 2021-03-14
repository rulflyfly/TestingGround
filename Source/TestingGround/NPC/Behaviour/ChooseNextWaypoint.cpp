// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
    
    UPatrollingComponent* PatrolRoute = Pawn->FindComponentByClass<UPatrollingComponent>();
    if (!ensure(PatrolRoute)) return EBTNodeResult::Failed;
    
    Waypoints = PatrolRoute->GetWaypoints();
    
    BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, Waypoints[Index]);
    
    int32 NextIndex = (Index + 1) % Waypoints.Num();
    BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
    
    return EBTNodeResult::Succeeded;
}
