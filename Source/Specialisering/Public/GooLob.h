// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "GooLob.generated.h"

/**
 * 
 */
UCLASS()
class SPECIALISERING_API AGooLob : public AProjectileBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	void SetDirection(FVector aDir) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AActor> myProjectile;

	float myGravity;

protected:
	virtual void BeginPlay() override;
};
