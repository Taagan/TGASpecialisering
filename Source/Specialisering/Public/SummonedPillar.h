// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "SummonedPillar.generated.h"

/**
 * 
 */
UCLASS()
class SPECIALISERING_API ASummonedPillar : public AProjectileBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	void SetDirection(FVector aDir) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector myDesirerdLocation;
};
