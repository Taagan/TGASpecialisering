// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "Goo.generated.h"

/**
 * 
 */
UCLASS()
class SPECIALISERING_API AGoo : public AProjectileBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float myLingerTime;
	float myTimer;
};
