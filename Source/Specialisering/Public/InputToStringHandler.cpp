#include "InputToStringHandler.h"

InputToStringHandler::InputToStringHandler()
{
	myInnerCircleRadius = 100.f;
	myOuterCircleRadius = 150.f;
	myRingPointRadius = (myOuterCircleRadius - myInnerCircleRadius) * 0.75f;

	myInputString = "";
}

const FVector2D InputToStringHandler::SendInput(const FVector2D& aMouseDelta)
{
	myInputPathSizePrevFrame = myInputPath.size();
	myCursorPos += aMouseDelta * FVector2D(10.f, 10.f);

	if (myCursorPos.SquaredLength() >= myOuterCircleRadius * myOuterCircleRadius)
	{
		FVector2D posDir = myCursorPos.GetSafeNormal();
		myCursorPos = posDir * myOuterCircleRadius;
	}

	if (myCursorPos.SquaredLength() >= myInnerCircleRadius * myInnerCircleRadius && myIsOutsideCenterCircle == false)
	{
		ExitCircle();
		return FVector2D::ZeroVector;
	}
	else if (myCursorPos.SquaredLength() < myInnerCircleRadius * myInnerCircleRadius && myIsOutsideCenterCircle == true)
	{
		EnterCircle();
		return FVector2D::ZeroVector;
	}

	if (myIsOutsideCenterCircle == false)
	{
		return FVector2D::ZeroVector;
	}

	if (abs(myLapAmount) == 1)
	{
		if ((myCursorPos - myPreviousRingPoint).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			myCurrentInput += 4;
			++myLapAmount;
			ResetCursor();
			return FVector2D::ZeroVector;
		}
	}

	if (myLapAmount == 0)
	{
		FVector2D rightRingPoint = { myCurrentRingPoint.Y, myCurrentRingPoint.X };
		FVector2D leftRingPoint = { -myCurrentRingPoint.Y, myCurrentRingPoint.X };
		if ((myCursorPos - rightRingPoint).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			myCurrentInput += 1;
			myPreviousRingPoint = myCurrentRingPoint;
			myCurrentRingPoint = rightRingPoint;
			++myLapAmount;
			myInputPath.emplace_back(myCurrentRingPoint);
			return myCurrentRingPoint;
		}
		else if((myCursorPos - leftRingPoint).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			myCurrentInput += 2;
			myPreviousRingPoint = myCurrentRingPoint;
			myCurrentRingPoint = leftRingPoint;
			--myLapAmount;
			myInputPath.emplace_back(myCurrentRingPoint);
			return myCurrentRingPoint;
		}
	}
	else if(myLapAmount > 0)
	{
		FVector2D rightRingPoint = { myCurrentRingPoint.Y, myCurrentRingPoint.X };
		if ((myCursorPos - rightRingPoint).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			++myCurrentInput;
			myPreviousRingPoint = myCurrentRingPoint;
			myCurrentRingPoint = rightRingPoint;
			++myLapAmount;
			myInputPath.emplace_back(myCurrentRingPoint);
			return myCurrentRingPoint;
		}
	}
	else
	{
		FVector2D leftRingPoint = { -myCurrentRingPoint.Y, myCurrentRingPoint.X };
		if ((myCursorPos - leftRingPoint).SquaredLength() <= myRingPointRadius * myRingPointRadius)
		{
			++myCurrentInput;
			myPreviousRingPoint = myCurrentRingPoint;
			myCurrentRingPoint = leftRingPoint;
			--myLapAmount;
			myInputPath.emplace_back(myCurrentRingPoint);
			return myCurrentRingPoint;
		}
	}

	if (abs(myLapAmount) == 4)
	{
		ResetCursor();
	}

	return FVector2D::ZeroVector;
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
	myInputString += myCurrentInput;
	++myCurrentStringIndex;
}

void InputToStringHandler::ResetCursor()
{
	EnterCircle();
	myCursorPos = { 0.f, 0.f };
}

const std::string InputToStringHandler::RetrieveString()
{
	std::string returnString = myInputString;
	myInputString = "";
	myCurrentStringIndex = 0;
	myIsOutsideCenterCircle = false;
	myCursorPos = { 0.f, 0.f };
	return returnString;
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
