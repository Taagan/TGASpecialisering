// Fill out your copyright notice in the Description page of Project Settings.


#include "Goo.h"

void AGoo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = GetActorRotation();
	SetActorRotation({ 0., 0., rotation.Euler().Z });

	myTimer += DeltaTime;
	if (myTimer >= myLingerTime)
	{
		Destroy();
	}
}

void AGoo::BeginPlay()
{
	Super::BeginPlay();

	myTimer = 0.f;
}
