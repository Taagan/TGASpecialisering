// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPECIALISERING_API UPHUD : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	void SetCrosshairPos(const FVector2D& aPos);
	void AddComboLine(const FVector2D& aStartPos, const FVector2D& aEndPos);
	void SetComboPoints(const FVector2D& aPos);
	void ClearComboLines();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myCrosshair; 
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myComboLine1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myRingPoint1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myRingPoint2;
};
