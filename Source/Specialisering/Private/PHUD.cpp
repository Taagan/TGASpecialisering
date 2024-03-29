// Fill out your copyright notice in the Description page of Project Settings.


#include "PHUD.h"
#include "Components\Image.h"

void UPHUD::Init()
{
	myComboLines.emplace_back(myComboLine1);
	myComboLines.emplace_back(myComboLine2);
	myComboLines.emplace_back(myComboLine3);
	myComboLines.emplace_back(myComboLine4);
	myComboLines.emplace_back(myComboLine5);
	myCurrentComboLine = 0;

	myComboImageSelection.emplace_back(myUpImage);

	myComboImageSelection.emplace_back(myUpQaurtRightImage);
	myComboImageSelection.emplace_back(myUpHalfRightImage);
	myComboImageSelection.emplace_back(myUpThreeQuartRightImage);
	myComboImageSelection.emplace_back(myUpFullImage);
	myComboImageSelection.emplace_back(myUpZRightImage);

	myComboImageSelection.emplace_back(myUpQuartLeftImage);
	myComboImageSelection.emplace_back(myUpHalfLeftImage);
	myComboImageSelection.emplace_back(myUpThreeQuartLeftImage);
	myComboImageSelection.emplace_back(myUpFullImage);
	myComboImageSelection.emplace_back(myUpZLeftImage);
}

void UPHUD::SetCrosshairPos(const FVector2D& aPos)
{
	FWidgetTransform transform;
	transform.Translation = aPos;

	myCrosshair->SetRenderTransform(transform);
}

void UPHUD::AddComboLine(const FVector2D& aPos)
{
	FWidgetTransform transform;
	FVector2D endPos(aPos.X, aPos.Y);

	FVector2D startPos = FVector2D::ZeroVector;
	if (myCurrentComboLine > 0 && myCurrentComboLine < myComboLines.size())
	{
		FVector2D pos = myComboLines[myCurrentComboLine - 1]->GetRenderTransform().Translation;
		float rot = myComboLines[myCurrentComboLine - 1]->GetRenderTransform().Angle;
		startPos = pos + (FVector2D(cosf(rot * 0.0174532925), sinf(rot * 0.0174532925)) * (pos.Length()));
	}

	transform.Translation = (endPos + startPos) * 0.5f;
	FVector2D deltaVector = endPos - startPos;
	transform.Scale = { deltaVector.Length(), 15.f };
	transform.Angle = atan2f(deltaVector.Y, deltaVector.X) * 57.2957795;

	myComboLines[myCurrentComboLine]->SetRenderTransform(transform);

	++myCurrentComboLine;
	UE_LOG(LogTemp, Display, TEXT("Combo"));
}

void UPHUD::SetComboPoints(const FVector2D& aPos)
{
	FWidgetTransform transform;
	transform.Scale = { 20.f, 20.f };

	/*float rot = atan2f(aLeftPos.Y, aLeftPos.X);
	float halfPI = (PI * 05.f) * 57.2957795;
	float length = aLeftPos.Length();
	float posRot = rot + halfPI;
	float negRot = rot - halfPI;

	FVector2D leftRingPoint = FVector2D(cosf(posRot), sinf(negRot)) * length;
	FVector2D rightRingPoint = FVector2D(cosf(negRot), sinf(posRot)) * length;*/

	FVector2D leftRingPoint = { -aPos.Y, aPos.X };
	FVector2D rightRingPoint = { aPos.Y, -aPos.X };

	//rightRingPoint.Y *= -1;
	transform.Translation = rightRingPoint;
	myRingPoint1->SetRenderTransform(transform);

	//leftRingPoint.Y *= -1;
	transform.Translation = leftRingPoint;
	myRingPoint2->SetRenderTransform(transform);
}

void UPHUD::AddComboImage(int aSize, int aImageIndex)
{
	//aSize -= 1;

	if (aSize == 0 || aSize <= myComboImages.size())
	{
		return;
	}

	myComboImages.emplace_back();

	UWorld* World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();
	myComboImages.back() = CreateWidget<UUserWidget>(PlayerController, myComboImageSelection[(aImageIndex - 2) % 11]);
	myComboImages.back()->AddToPlayerScreen();

	FWidgetTransform transform;
	transform.Angle = ((aImageIndex - 2) / 11) * 90.f;
	myComboImages.back()->SetRenderTransform(transform);

	int iterations = 0;
	for (auto& image : myComboImages)
	{
		transform = image->RenderTransform;
		//image->RemoveFromParent();

		transform.Translation = FVector2D((60.f * iterations) - (60.f * (aSize - 1) * 0.5f), 200.f);

		image->SetRenderTransform(transform);
		//image->AddToPlayerScreen();

		++iterations;
	}
}

void UPHUD::ClearComboLines()
{
	FWidgetTransform transform;
	transform.Scale = { .0f, 0.f };

	myComboLine1->SetRenderTransform(transform);
	myComboLine2->SetRenderTransform(transform);
	myComboLine3->SetRenderTransform(transform);
	myComboLine4->SetRenderTransform(transform);
	myComboLine5->SetRenderTransform(transform);

	myRingPoint1->SetRenderTransform(transform);
	myRingPoint2->SetRenderTransform(transform);

	myCurrentComboLine = 0;
}

void UPHUD::ClearCombo()
{
	ClearComboLines();

	for (auto& image : myComboImages)
	{
		image->RemoveFromParent();
	}

	myComboImages.clear();
}
