// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
    GENERATED_USTRUCT_BODY()
    
    FVector Location;
    float YawRotation;
    float Scale;
    
};

UCLASS()
class TESTINGGROUND_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Navigation Pool")
    class UActorPool* NavPool;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    
    

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    UFUNCTION(BlueprintCallable)
    void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);
    
    UFUNCTION(BlueprintCallable)
    void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500);
    
    UFUNCTION(BlueprintCallable)
    void SetNavPool(UActorPool* Pool);
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
    FVector MinExtent;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
    FVector MaxExtent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props")
    TArray<AActor*> Props;

private:
    bool CanSpawnAtLocation(FVector Location, float Radius);
    
    AActor* NavMeshBoundsVolume;
    
    void PositionNavMeshBoundsVolume();
    
    template<class T>
    void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);
    
    bool FoundEmptySpot(FVector& OutLocation, float Radius);
    void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition);
    void PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition);

};
