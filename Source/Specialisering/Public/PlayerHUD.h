// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPECIALISERING_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, Category = "Player")
	class UImage* myCrosshair;
};
