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
	//MyQueryRequest = FEnvQueryRequest(myQuery, myPlayer);
}

// Called every frame
void AAIDirectorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIDirectorActor::RunDirector(const FTransform& aTransform, const TSubclassOf<AActor>& anActor)
{
	if (myEnemyCount >= myEnemyLimit)
	{
		return;
	}
}


void AAIDirectorActor::ForceSpawnEnemy(const FVector& aPosition, const TSubclassOf<AActor>& anActor, AActor*& outActor)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FTransform transform({ 0,0,0 }, aPosition, {1,1,1 });

	outActor = GetWorld()->SpawnActor<AActor>(anActor, transform,params);
	myEnemies.Emplace(outActor);
	myEnemyCount++;
}

void AAIDirectorActor::SpawnEnemy(const FVector& aPosition, const TSubclassOf<AActor>& anActor, AActor*& outActor)
{
	if (myEnemyCount >= myEnemyLimit)
	{
		return;
	}
	ForceSpawnEnemy(aPosition, anActor, outActor);
}

void AAIDirectorActor::SpawnEnemyAroundLocation(bool& aSuccsess,const FVector& aPosition, const TSubclassOf<AActor>& anActor, AActor*& outActor)
{
	if (myEnemyCount >= myEnemyLimit)
	{
		aSuccsess = false;
		return;
	}
	int ran = FMath::RandRange(0, 359);
	float radians = ran * (3.14159 / 180);
	auto x = FMath::Cos(radians);
	auto y = FMath::Sin(radians);
	double distance = FMath::RandRange(myEnemyMinSpawnDistance, myEnemyMaxSpawnDistance);
	x *= distance;
	y *= distance;
	FVector newPos = aPosition;
	newPos.X += x;
	newPos.Y += y;
	newPos.Z += 100;
	aSuccsess = true;
	SpawnEnemy(newPos, anActor, outActor);
}

void AAIDirectorActor::GetLocationAroundPlayer(FVector& outPosition)
{
	int ran = FMath::RandRange(0, 359);
	float radians = ran * (3.14159 / 180);
	auto x = FMath::Cos(radians);
	auto y = FMath::Sin(radians);
	double distance = FMath::RandRange(myEnemyMinSpawnDistance, myEnemyMaxSpawnDistance);
	x *= distance;
	y *= distance;
	FVector newPos = myPlayer->GetActorLocation();
	newPos.X += x;
	newPos.Y += y;
	newPos.Z += 100;
	outPosition = newPos;
}

void AAIDirectorActor::AddIntrestPoint(const FVector& aPoint, const TSubclassOf<AActor>& anActor)
{
	FTransform transform;
	transform.SetLocation(aPoint);
	FInterestPointInfo info(anActor,transform);
	myIntrestPoints.emplace_back(info);
}

void AAIDirectorActor::SpawnInterestPoint(const int anIndex, AActor*& outActor)
{
	ForceSpawnEnemy(myIntrestPoints[anIndex].transform.GetLocation(), myIntrestPoints[anIndex].actor, outActor);
}

void AAIDirectorActor::GetEnemies(TArray<AActor*>& someActors)
{
	someActors = myEnemies;
}

void AAIDirectorActor::RemoveActor(AActor* anActor, AActor*& aRemovedActor)
{
	int32 index = myEnemies.Find(anActor);
	if (index != -1)
	{
		myEnemies[index] = myEnemies.Pop();
		myEnemyCount--;
	}
	aRemovedActor = anActor;
}

void AAIDirectorActor::ReadyToSpawn(const float& aDeltaTime,const float& aScoreMultiplier, bool& outReady)
{
	if (myCurrentStage == AIDStage::Relaxed)
	{
		myRelaxTimer += aDeltaTime;
		if (myRelaxTimer >= myRelaxTime)
		{
			StartRamp();
		}
		outReady = false;
		return;
	}
	mySpawnTimer += aDeltaTime;
	float time = mySpawnTime - myScore * aScoreMultiplier;
	if (mySpawnTimer >= time || myCurrentStage == AIDStage::Peak)
	{
		outReady = true;
		mySpawnTimer = 0;
		if (myCurrentStage == AIDStage::Ramp)
		{
			myRampCounter++;
			if (myRampCounter >= 15.f)
			{
				StartPeak();
			}
		}
		else if (myCurrentStage == AIDStage::Peak && myEnemyCount >= myEnemyPeakAmount)
		{
			StartRelax();
		}
	}
	else
	{
		outReady = false;
	}
}

void AAIDirectorActor::SetPlayer(AActor* anActor)
{
	myPlayer = anActor;
}

void AAIDirectorActor::IncreaseScore(const int& anIncrease)
{
	myScore = anIncrease;
}

void AAIDirectorActor::DecreaseScore(const int& anDecrease)
{
	myScore = anDecrease;
}

void AAIDirectorActor::StartRamp()
{
	myCurrentStage = AIDStage::Ramp;
	myRelaxTimer = 0;
	myRampCounter = 0;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Starting to Ramp"));
}


void AAIDirectorActor::StartPeak()
{
	myCurrentStage = AIDStage::Peak;
	myEnemyPeakAmount = static_cast<int>(myEnemyLimit * 0.25f);
	myRampCounter = 0;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Reached Peak"));
}


void AAIDirectorActor::StartRelax()
{
	myCurrentStage = AIDStage::Relaxed;
	myRampCounter = 0;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Going Relax"));
}
