// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunStateMachineBase.h"
#include "GunBase.generated.h"

class AFPSController;

UCLASS()
class SPECIALISERING_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	GunStateMachineBase* myGunStateMachine;

	UPROPERTY(EditAnywhere, Category = "Gun")
	TSubclassOf<AActor> myStandardProjectile;
	UPROPERTY(EditAnywhere, Category = "Gun")
	TSubclassOf<AActor> myWallProjectile;
	UPROPERTY(EditAnywhere, Category = "Gun")
	TSubclassOf<AActor> myGoopLobProjectile;

	AFPSController* myController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attach(AFPSController* aController);

	void ParseInputStringToGun(const std::string aString);
	void ForwardShootAction();

	void Shoot(int aProjectileID);

};
