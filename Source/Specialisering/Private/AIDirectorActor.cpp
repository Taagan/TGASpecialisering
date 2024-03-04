// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDirectorActor.h"

// Sets default values
AAIDirectorActor::AAIDirectorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIDirectorActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAIDirectorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mySpawntimer += DeltaTime;
}

void AAIDirectorActor::RunDirector(const FTransform& aTransform, const TSubclassOf<AActor>& anActor)
{
	if (myEnemyCount >= myEnemyLimit || mySpawntimer < mySpawnTime)
	{
		return;
	}
	mySpawntimer = 0;
	//ForceSpawnEnemy(aTransform, anActor);
	static bool flip = false;
	SpawnInterestPoint(flip);
	flip = !flip;
}


void AAIDirectorActor::ForceSpawnEnemy(const FTransform& aTransform, const TSubclassOf<AActor>& anActor)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(anActor, aTransform,params);
	myEnemyCount++;
}

void AAIDirectorActor::AddIntrestPoint(const FVector& aPoint, const TSubclassOf<AActor>& anActor)
{
	FTransform transform;
	transform.SetLocation(aPoint);
	FInterestPointInfo info(anActor,transform);
	myIntrestPoints.emplace_back(info);
}

void AAIDirectorActor::SpawnInterestPoint(const int anIndex)
{
	for (size_t i = 0; i < myMobSize; i++)
	{
		ForceSpawnEnemy(myIntrestPoints[anIndex].transform, myIntrestPoints[anIndex].actor);
	}
}

