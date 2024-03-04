// Fill out your copyright notice in the Description page of Project Settings.


#include "PHUD.h"
#include "Components\Image.h"

void UPHUD::SetCrosshairPos(const FVector2D& aPos)
{
	FWidgetTransform transform;
	transform.Translation = aPos;

	myCrosshair->SetRenderTransform(transform);
}

void UPHUD::AddComboLine(const FVector2D& aStartPos, const FVector2D& aEndPos)
{
	FWidgetTransform transform;
	FVector2D endPos(aEndPos.X, -aEndPos.Y);
	transform.Translation = (endPos + aStartPos) * 0.5f;
	FVector2D deltaVector = endPos - aStartPos;
	transform.Scale = { deltaVector.Length(), 15.f };
	transform.Angle = atan2f(deltaVector.Y, deltaVector.X) * 57.2957795;

	myComboLine1->SetRenderTransform(transform);
}

void UPHUD::SetComboPoints(const FVector2D& aLeftPos)
{
	FWidgetTransform transform;
	FVector2D pos(aLeftPos.Y, aLeftPos.X);
	transform.Translation = pos;
	transform.Scale = { 20.f, 20.f };

	myRingPoint1->SetRenderTransform(transform);

	pos = { -aLeftPos.Y, aLeftPos.X };
	transform.Translation = pos;

	myRingPoint2->SetRenderTransform(transform);
}

void UPHUD::ClearComboLines()
{
	FWidgetTransform transform;
	transform.Scale = { .0f, 0.f };

	myComboLine1->SetRenderTransform(transform);
}
