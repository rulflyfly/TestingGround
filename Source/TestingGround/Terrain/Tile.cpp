// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "../ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    
    MinExtent = FVector(0, -2000, 50);
    MaxExtent = FVector(4000, 2000, 50);
    
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::SetNavPool(UActorPool* Pool)
{
    NavPool = Pool;
    
    PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
    NavMeshBoundsVolume = NavPool->Checkout();
    
    if (!NavMeshBoundsVolume)
    {
        UE_LOG(LogTemp, Warning, TEXT("THE POOL IS EMPTY"));
        return;
    }
    
    NavMeshBoundsVolume->SetActorLocation(GetActorLocation());

    FNavigationSystem::Build(*GetWorld());
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    
    NavPool->Return(NavMeshBoundsVolume);
}

bool ATile::FoundEmptySpot(FVector& OutLocation, float Radius)
{
    FBox Bounds(MinExtent, MaxExtent);
    
    const int32 MAX_ATTEMPTS = 100;
    
    for (int32 i = 0; i <= MAX_ATTEMPTS; i++)
    {
        FVector PointToCheck = FMath::RandPointInBox(Bounds);
        if (CanSpawnAtLocation(PointToCheck, Radius))
        {
            OutLocation = PointToCheck;
            return true;
        }
    }
    
    return false;
}



bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
    FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
    FHitResult HitResult;
    bool HasHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        GlobalLocation,
        GlobalLocation,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel2,
        FCollisionShape::MakeSphere(Radius)
    );
    
//    FColor ResultColor;
//
//    ResultColor = HasHit ? FColor::Red : FColor::Green;
//
//    DrawDebugSphere
//    (
//        GetWorld(),
//        GlobalLocation,
//        Radius,
//        20,
//        ResultColor,
//        true,
//        1000,
//        false,
//        3
//     );
    
    return !HasHit;
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
    if (!ToSpawn) return;
    RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius)
{
    if (!ToSpawn) return;
    RandomlyPlaceActors(ToSpawn, MinSpawn, MaxSpawn, Radius);
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition)
{
    FRotator Rotation = FRotator(0, SpawnPosition.YawRotation, 0);
    APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn, SpawnPosition.Location, Rotation);
    if (!Spawned) return;
    // we need to attach to Tile so that the relative location is relative to the Tile
    Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    
    Spawned->SpawnDefaultController();
    
    Props.Add(Spawned);
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
    AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
    if (!Spawned) return;
    Spawned->SetActorRelativeLocation(SpawnPosition.Location);
    Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    Spawned->SetActorRotation(FRotator(0, SpawnPosition.YawRotation, 0));
    Spawned->SetActorRelativeScale3D(FVector(SpawnPosition.Scale));
    
    Props.Add(Spawned);
}

/** you might need to declare a template before you use it */
template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
    int32 SpawnCount = FMath::RandRange(MinSpawn, MaxSpawn);
    
    for (int32 i = 0; i < SpawnCount; i++)
    {
        FSpawnPosition SpawnPosition;
        SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
        
        if (FoundEmptySpot(SpawnPosition.Location, Radius * SpawnPosition.Scale))
        {
            SpawnPosition.YawRotation = FMath::RandRange(-180.f, 180.f);
            PlaceActor(ToSpawn, SpawnPosition);
        }
    }
}
