// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "FPSController.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	
	myGunStateMachine->Init(this);
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	myGunStateMachine->Update(DeltaTime);
}

void AGunBase::Attach(AFPSController* aController)
{
	myController = aController;
}

void AGunBase::ParseInputStringToGun(const std::string& aString)
{
	myGunStateMachine->RequestStateChangeString(aString);
}

void AGunBase::ForwardShootAction()
{
	myGunStateMachine->SendMouseInput();
}

void AGunBase::Shoot()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(myController->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector SpawnLocation = GetActorLocation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// Spawn the projectile at the muzzle
		World->SpawnActor<AActor>(myProjectile, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}

