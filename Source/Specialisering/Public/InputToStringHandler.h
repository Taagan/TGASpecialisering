#pragma once
#include "CoreMinimal.h"
#include <string>
#include <vector>
#include "InputStringTypes.h"

class InputToStringHandler
{
public:
	InputToStringHandler();
	~InputToStringHandler() = default;

	const FVector2D SendInput(const FVector2D& aMouseDelta);

	void ExitCircle();
	void EnterCircle();
	void ResetCursor();

	const std::string RetrieveString();
	const FVector2D& GetCursorPos();
	const std::vector<FVector2D>& GetInputPath();
	const bool HasInputPathChanged();

private:
	std::vector<FVector2D> myInputPath;

	std::string myInputString;

	FVector2D myCursorPos;
	FVector2D myInitialExitDir;
	FVector2D myCurrentRingPoint;
	FVector2D myPreviousRingPoint;

	float myInnerCircleRadius;
	float myOuterCircleRadius;
	float myRingPointRadius;

	int myCurrentStringIndex;
	int myLapAmount;
	int myInputPathSizePrevFrame;

	char myCurrentInput;

	bool myIsOutsideCenterCircle;
};