// Fill out your copyright notice in the Description page of Project Settings.


#include "GooLob.h"

void AGooLob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AProjectileBase::Tick(DeltaTime);
	myGravity -= 1800.f * DeltaTime;
	AddActorWorldOffset({ 0.f, 0.f, myGravity * DeltaTime });
}

void AGooLob::SetDirection(FVector aDir)
{
	myDirection.X = aDir.X;
	myDirection.Y = aDir.Y;
	myDirection.Z = aDir.Z + 2.f;
	myDirection.Normalize();
}

void AGooLob::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (Cast<AGooLob>(OtherActor))
	{
		return;
	}

	AProjectileBase::NotifyActorBeginOverlap(OtherActor);

	if (Cast<APawn>(OtherActor) || Cast<AProjectileBase>(OtherActor))
	{
		return;
	}

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		const FRotator SpawnRotation(GetActorRotation());
		const FVector SpawnLocation = GetActorLocation() - FVector(0.f, 0.f, 50);

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//TSubclassOf<AActor> projectileClass = *Cast<TSubclassOf<AActor>>(OtherActor);

		// Spawn the projectile at the muzzle
		auto projectile = World->SpawnActor<AActor>(myProjectile, SpawnLocation, SpawnRotation, ActorSpawnParams);
		dynamic_cast<AProjectileBase*>(projectile)->SetDirection(FVector(cosf(SpawnRotation.Yaw), sinf(SpawnRotation.Yaw), 0.f));
	}
	//Destroy();
}

void AGooLob::BeginPlay()
{
	Super::BeginPlay();
	myGravity = 0.f;
}
