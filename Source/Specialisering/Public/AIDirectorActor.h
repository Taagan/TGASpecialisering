// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIDirectorActor.generated.h"
//#include <Runtime/AIModule/Classes/EnvironmentQuery/EnvQuery.h>
//#include <Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryTypes.h>
//#include <Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryManager.h>

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

UENUM(BlueprintType)
enum class AIDStage
{
	Relaxed,
	Ramp,
	Peak
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
	void SpawnEnemyAroundLocation(bool& aSuccess,const FVector& aPosition, const TSubclassOf<AActor>& anActor, AActor*& outActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void GetLocationAroundPlayer(FVector& outPosition);

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
	void ReadyToSpawn(const float& aDeltaTime, const float& aScoreMultiplier,bool& outReady);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void SetPlayer(AActor* anActor);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void IncreaseScore(const int& anIncrease);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void DecreaseScore(const int& anDecrease);

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void StartRamp();

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void StartPeak();

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void StartRelax();

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void PunishPlayer();

	UFUNCTION(BlueprintCallable, Category = "AIDirector")
	void StopPunishingPlayer();


	//void QueryFinished(TSharedPtr<FEnvQueryResult> Result);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> myEnemyClass;

	std::vector<FInterestPointInfo> myIntrestPoints;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> myEnemies;

	UPROPERTY(VisibleAnywhere)
	AActor* myPlayer;


	UPROPERTY(EditAnywhere)
	float myScore;

	UPROPERTY(EditAnywhere)
	float mySpawnTime;
	float mySpawnTimer;

	UPROPERTY(EditAnywhere)
	float myRampBeforePeakCount;

	UPROPERTY(EditAnywhere)
	float myRelaxBaseTime;
	float myRelaxTime;
	float myRelaxTimer;

	float myRampCounter;

	UPROPERTY(EditAnywhere)
	int myEnemyLimit;
	int myEnemyCount;

	int myEnemyPeakAmount;

	UPROPERTY(EditAnywhere)
	int myEnemyMinSpawnDistance;
	UPROPERTY(EditAnywhere)
	int myEnemyMaxSpawnDistance;

	UPROPERTY(EditAnywhere)
	AIDStage myCurrentStage;

	UPROPERTY(EditAnywhere)
	bool myPunishPlayer;
 };
