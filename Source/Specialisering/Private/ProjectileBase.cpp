// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (myTravelledRange >= myMaxRange)
	{
		Destroy();
	}

	float distToMove = mySpeed * DeltaTime;
	if (myTravelledRange + distToMove > myMaxRange)
	{
		distToMove = myMaxRange - myTravelledRange;
	}

	AddActorWorldOffset(myDirection * distToMove);
	myTravelledRange += distToMove;
}

void AProjectileBase::SetDirection(FVector aDir)
{
	myDirection = aDir;
}

void AProjectileBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	--myPierce;
	if (myPierce <= 0)
	{
		Destroy();
	}
}

