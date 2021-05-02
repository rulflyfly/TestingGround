// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestingGroundGameMode.h"
#include "TestingGroundHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "ActorPool.h"

ATestingGroundGameMode::ATestingGroundGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
//	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Blueprint'/Game/FP/Blueprints/MainCharacter.MainCharacter'"));
//	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingGroundHUD::StaticClass();
    
    NavPool = CreateDefaultSubobject<UActorPool>(TEXT("NavPool"));
}

void ATestingGroundGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    //PopulateBoundsVolumePool();
}

void ATestingGroundGameMode::PopulateBoundsVolumePool()
{
    auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
    while (VolumeIterator)
    {
        NavPool->Add(*VolumeIterator);
    
        ++VolumeIterator;
    }
}
