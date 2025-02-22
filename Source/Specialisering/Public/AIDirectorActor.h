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
	void ForceSpawnEnemy(const FTransform& aTransform, const TSubclassOf<AActor>& anActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void RunDirector(const FTransform& aPlayerTransform, const TSubclassOf<AActor>& anActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void AddIntrestPoint(const FVector& aPoint, const TSubclassOf<AActor>& anActor);

	void SpawnInterestPoint(const int anIndex);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> myEnemyClass;

	std::vector<FInterestPointInfo> myIntrestPoints;

	UPROPERTY(EditAnywhere)
	float mySpawnTime;
	float mySpawntimer;

	UPROPERTY(EditAnywhere)
	float myMobSize;

	UPROPERTY(EditAnywhere)
	int myEnemyLimit;
	int myEnemyCount;

};
