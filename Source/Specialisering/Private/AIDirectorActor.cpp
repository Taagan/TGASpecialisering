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
}

void AAIDirectorActor::SpawnEnemy(const FTransform& aTransform, const TSubclassOf<AActor>& anActor)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(anActor, aTransform, params);
	//FEnemy enemy;
	//enemy.transform = aTransform;
	//enemy.object = anActor;
	//enemy.spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	//GetWorld()->SpawnActor<AActor>(enemy.object, enemy.transform, enemy.spawnParameters);
	//myEnemies.Emplace(enemy);
}

