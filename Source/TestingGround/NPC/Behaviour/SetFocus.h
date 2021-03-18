// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SetFocus.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUND_API USetFocus : public UBTTaskNode
{
	GENERATED_BODY()
	
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    
protected:
    UPROPERTY(EditAnywhere, Category = Blackboard)
    struct FBlackboardKeySelector FocusActorKey;
};
