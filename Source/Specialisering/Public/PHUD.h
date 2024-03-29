// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include	<vector>
#include "PHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPECIALISERING_API UPHUD : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	void Init();
	void SetCrosshairPos(const FVector2D& aPos);
	void AddComboLine(const FVector2D& aPos);
	void SetComboPoints(const FVector2D& aPos);
	void AddComboImage(int aSize, int aImageIndex);
	void ClearComboLines();
	void ClearCombo();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myCrosshair; 
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myComboLine1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myComboLine2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myComboLine3;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myComboLine4;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myComboLine5;

	std::vector<UImage*> myComboLines;
	int myCurrentComboLine;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myRingPoint1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* myRingPoint2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpImage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpZLeftImage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpZRightImage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpQuartLeftImage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpQaurtRightImage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpHalfLeftImage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpHalfRightImage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpThreeQuartLeftImage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpThreeQuartRightImage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> myUpFullImage;
	std::vector<TSubclassOf<UUserWidget>> myComboImageSelection;

	std::vector<UUserWidget*> myComboImages;
};
