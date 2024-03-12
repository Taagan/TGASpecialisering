// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIDirectorActor.generated.h"

USTRUCT()
struct FInterestPointInfo
{
	GENERATED_BODY()
	FInterestPointInfo()
	{

	}
	FInterestPointInfo(const TSubclassOf<AActor>& anActor,
		const FTransform& aTransform)
	{
		actor = anActor;
		transform = aTransform;
	}
	TSubclassOf<AActor> actor;
	FTransform transform;
};

UCLASS()
class SPECIALISERING_API AAIDirectorActor : public AActor
{
	GENERATED_BODY()
	



public:	
	// Sets default values for this actor's properties
	AAIDirectorActor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void ForceSpawnEnemy(const FVector& aPosition, const TSubclassOf<AActor>& anActor,AActor*& outActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void SpawnEnemy(const FVector& aPosition, const TSubclassOf<AActor>& anActor,AActor*& outActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void SpawnEnemyAroundLocation(const FVector& aPosition, const TSubclassOf<AActor>& anActor, AActor*& outActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void RunDirector(const FTransform& aPlayerTransform, const TSubclassOf<AActor>& anActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void AddIntrestPoint(const FVector& aPoint, const TSubclassOf<AActor>& anActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void SpawnInterestPoint(const int anIndex, AActor*& outActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void GetEnemies(TArray<AActor*>& someActors);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void RemoveActor(AActor* anActor,AActor*& aRemovedActor);


	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void ReadyToSpawn(const float& aDeltaTime,bool& outReady);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> myEnemyClass;

	std::vector<FInterestPointInfo> myIntrestPoints;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> myEnemies;

	UPROPERTY(EditAnywhere)
	float myScore;

	UPROPERTY(EditAnywhere)
	float mySpawnTime;
	float mySpawnTimer;

	UPROPERTY(EditAnywhere)
	int myEnemyLimit;
	int myEnemyCount;
	UPROPERTY(EditAnywhere)
	int myEnemyMinSpawnDistance;
	UPROPERTY(EditAnywhere)
	int myEnemyMaxSpawnDistance;

};
