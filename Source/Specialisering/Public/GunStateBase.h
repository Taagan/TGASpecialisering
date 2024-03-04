#pragma once
#include "InputStringTypes.h"

class GunStateMachineBase;

class GunStateBase
{
public:
	enum eStateTransitionJump : int
	{
		None,
		Single,
	};

	GunStateBase() = delete;
	GunStateBase(GunStateMachineBase* aGunStateMachine);
	virtual ~GunStateBase() = default;

	virtual void Enter() = 0;
	virtual eStateTransitionJump Update(float aDeltaTime) = 0;
	virtual void Exit() = 0; 

	void SendMouseInput() { myHasReceivedInputThisFrame = true; };

	const int GetPriority() const { return myPriority; };

private:
protected:
	GunStateMachineBase* myStateMachine;

	int myPriority;

	bool myHasReceivedInputThisFrame = false;
};