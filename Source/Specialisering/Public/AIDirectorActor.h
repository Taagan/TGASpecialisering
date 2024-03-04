// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIDirectorActor.generated.h"

UCLASS()
class SPECIALISERING_API AAIDirectorActor : public AActor
{
	GENERATED_BODY()
	



public:	
	// Sets default values for this actor's properties
	AAIDirectorActor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SpawnEnemy(const FTransform& aTransform, const TSubclassOf<AActor>& anActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> myEnemyClass;
	//TArray<FEnemy> myEnemies;
	//FEnemy spawnableEnemy;
};
