// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

enum class ProjetileType
{
	Standard,
	WallStick,
	Pierce,
	Linger
};

UCLASS()
class SPECIALISERING_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector myDirection;
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float mySpeed;
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float myMaxRange;
	float myTravelledRange;
	UPROPERTY(EditAnywhere, Category = "Projectile")
	int myPierce;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetDirection(FVector aDir);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
