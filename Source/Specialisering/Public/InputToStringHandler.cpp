#include "InputToStringHandler.h"

InputToStringHandler::InputToStringHandler()
{
	myInnerCircleRadius = 100.f;
	myOuterCircleRadius = 150.f;
	myRingPointRadius = (myOuterCircleRadius - myInnerCircleRadius) * 1.75f;

	myBlockInputTimer = 0.f;
	myBlockInputDelay = 0.115f;

	myInputString = "";
	myCurrentInput = 0;
}

InputToStringHandler::~InputToStringHandler()
{
	myInputString = "END";
	myInputPath.clear();
}

void InputToStringHandler::Tick(float aDeltaTime)
{
	myBlockInputTimer += aDeltaTime;

	myInputPathSizePrevFrame = myInputPath.size();
}

void InputToStringHandler::SendInput(const FVector2D& aMouseDelta)
{
	if (myBlockInputTimer < myBlockInputDelay)
	{
		return;
	}

	myCursorPos += aMouseDelta * FVector2D(10.f, 10.f);

	if (myCursorPos.SquaredLength() >= myOuterCircleRadius * myOuterCircleRadius)
	{
		FVector2D posDir = myCursorPos.GetSafeNormal();
		myCursorPos = posDir * myOuterCircleRadius;
	}

	if (myCursorPos.SquaredLength() >= myInnerCircleRadius * myInnerCircleRadius && myIsOutsideCenterCircle == false)
	{
		ExitCircle();
		return;
	}
	else if (myCursorPos.SquaredLength() < myInnerCircleRadius * myInnerCircleRadius && myIsOutsideCenterCircle == true)
	{
		ResetCursor();
		return;
	}

	if (myIsOutsideCenterCircle == false)
	{
		return;
	}

	if (abs(myLapAmount) == 4)
	{
		ResetCursor();
	}

	if (abs(myLapAmount) == 1)
	{
		if ((myCursorPos - FVector2D(myPreviousRingPoint.X, -myPreviousRingPoint.Y)).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			myCurrentInput += 4;
			++myLapAmount;
			ResetCursor();
			return;
		}
	}

	/*float rot = atan2f(myCurrentRingPoint.Y, myCurrentRingPoint.X);
	float halfPI = (PI * 05.f) * 57.2957795;
	float length = myCurrentRingPoint.Length();
	float posRot = rot + halfPI;
	float negRot = rot - halfPI;

	FVector2D leftRingPoint = FVector2D(cosf(posRot), sinf(negRot)) * length;
	FVector2D rightRingPoint = FVector2D(cosf(negRot), sinf(posRot)) * length;*/

	FVector2D leftRingPoint = { myCurrentRingPoint.Y, -myCurrentRingPoint.X };
	FVector2D rightRingPoint = { -myCurrentRingPoint.Y, myCurrentRingPoint.X };

	if (myLapAmount == 0)
	{
		leftRingPoint.X = -leftRingPoint.X;
		rightRingPoint.X = -rightRingPoint.X;

		if ((myCursorPos - rightRingPoint).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			UE_LOG(LogTemp, Display, TEXT("Right"));
			myCurrentInput += 1;
			myPreviousRingPoint = myCurrentRingPoint;
			myCurrentRingPoint = rightRingPoint;
			++myLapAmount;
			myInputPath.emplace_back(myCurrentRingPoint);
			return;
		}
		else if((myCursorPos - leftRingPoint).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			UE_LOG(LogTemp, Display, TEXT("Left"));
			myCurrentInput += 6;
			myPreviousRingPoint = myCurrentRingPoint;
			myCurrentRingPoint = leftRingPoint;
			--myLapAmount;
			myInputPath.emplace_back(myCurrentRingPoint);
			return;
		}
	}
	else if(myLapAmount > 0)
	{
		if ((myCursorPos - rightRingPoint).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			UE_LOG(LogTemp, Display, TEXT("Right"));
			++myCurrentInput;
			myPreviousRingPoint = myCurrentRingPoint;
			myCurrentRingPoint = rightRingPoint;
			++myLapAmount;
			myInputPath.emplace_back(myCurrentRingPoint);
			return;
		}
	}
	else
	{
		if ((myCursorPos - leftRingPoint).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			UE_LOG(LogTemp, Display, TEXT("Left"));
			++myCurrentInput;
			myPreviousRingPoint = myCurrentRingPoint;
			myCurrentRingPoint = leftRingPoint;
			--myLapAmount;
			myInputPath.emplace_back(myCurrentRingPoint);
			return;
		}
	}
}

void InputToStringHandler::ExitCircle()
{
	myIsOutsideCenterCircle = true;
	if (abs(myCursorPos.X) > abs(myCursorPos.Y))
	{
		myInitialExitDir = { myInnerCircleRadius + myRingPointRadius, 0.f };

		if (myCursorPos.X > 0)
		{
			myCurrentInput = eInputStringTypes::RIGHT;
		}
		else
		{
			myCurrentInput = eInputStringTypes::LEFT;
			myInitialExitDir *= -1;
		}
	}
	else
	{
		myInitialExitDir = { 0.f, myInnerCircleRadius + myRingPointRadius };

		if (myCursorPos.Y < 0)
		{
			myCurrentInput = eInputStringTypes::UP;
		}
		else
		{
			myCurrentInput = eInputStringTypes::DOWN;
			myInitialExitDir *= -1;
		}
	}

	myCurrentRingPoint = myInitialExitDir;
	myInputPath.emplace_back(myCurrentRingPoint);
}

void InputToStringHandler::EnterCircle()
{
	myIsOutsideCenterCircle = false;
	myLapAmount = 0;
	if (myInputString.back() == 0)
	{
		myInputString.back() = myCurrentInput;
	}
	else
	{
		myInputString += myCurrentInput;
	}
	++myCurrentStringIndex;
	myInputPath.clear();
	myCurrentInput = 0;
}

void InputToStringHandler::ResetCursor()
{
	EnterCircle();
	myCursorPos = { 0.f, 0.f };
	myBlockInputTimer = 0.f;
}

const std::string InputToStringHandler::RetrieveString()
{
	if (myCurrentInput > 0)
	{
		myInputString += myCurrentInput;
	}
	std::string returnString = myInputString;
	myInputString.clear();
	myCurrentStringIndex = 0;
	myIsOutsideCenterCircle = false;
	ResetCursor();
	return returnString;
}

const std::string InputToStringHandler::PeakString()
{
	if (!myInputString.empty())
	{
		return myInputString;
	}
	return std::string();
}

const FVector2D& InputToStringHandler::GetCursorPos()
{
	return myCursorPos;
}

const std::vector<FVector2D>& InputToStringHandler::GetInputPath()
{
	return myInputPath;
}

const bool InputToStringHandler::HasInputPathChanged()
{
	return (myInputPathSizePrevFrame != myInputPath.size());
}
