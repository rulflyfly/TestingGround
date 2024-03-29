// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestingGroundGameMode.generated.h"

UCLASS(minimalapi)
class ATestingGroundGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestingGroundGameMode();
    
    UFUNCTION(BlueprintCallable)
    void PopulateBoundsVolumePool();
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Navigation Pool")
    class UActorPool* NavPool;
    
protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    
};



