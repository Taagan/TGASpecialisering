// Fill out your copyright notice in the Description page of Project Settings.


#include "SummonedPillar.h"

void ASummonedPillar::BeginPlay()
{
	Super::BeginPlay();

	myDesirerdLocation.Z = GetActorLocation().Z + 400.f;
}

void ASummonedPillar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation({
		GetActorLocation().X,
		GetActorLocation().Y,
		FMath::Lerp(GetActorLocation().Z, myDesirerdLocation.Z, DeltaTime) });

	/*AddActorWorldOffset(FVector(0.f, 0.f, 1.f) * GetActorLocation().Z - myDesirerdLocation.Z * DeltaTime);
	AddActorWorldRotation({ -GetActorRotation().Vector().X, -GetActorRotation().Vector().Y, 0. });*/

	FRotator rotation = GetActorRotation();
	SetActorRotation({ 0., 0., rotation.Euler().Z });

	AProjectileBase::Tick(DeltaTime);
}

void ASummonedPillar::SetDirection(FVector aDir)
{
	myDirection = aDir;
	myDirection.Z = 0.f;

	AddActorWorldOffset(myDirection * 100.f);
}

void ASummonedPillar::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AProjectileBase::NotifyActorBeginOverlap(OtherActor);

	if (AProjectileBase* otherProjectile = Cast<AProjectileBase>(OtherActor))
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < 8; i++)
			{
				const FRotator SpawnRotation(0.f, i * (360.f / 7.f), 0.f);
				const FVector SpawnLocation = GetActorLocation() - FVector(0.f, 0.f, 350.f) /*+ PlayerController->PlayerCameraManager->GetActorForwardVector() * 50.f*/;

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				//TSubclassOf<AActor> projectileClass = *Cast<TSubclassOf<AActor>>(OtherActor);

				// Spawn the projectile at the muzzle
				auto projectile = World->SpawnActor<AActor>(otherProjectile->GetClass(), SpawnLocation, SpawnRotation, ActorSpawnParams);
				dynamic_cast<AProjectileBase*>(projectile)->SetDirection(FVector(cosf(SpawnRotation.Yaw), sinf(SpawnRotation.Yaw), 0.f));
			}
		}

		Destroy();
	}
}
