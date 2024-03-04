#include "GSM_GenericTransitionState.h"

GSM_GenericTransitionState::GSM_GenericTransitionState(GunStateMachineBase* aGunStateMachine, int aPriority, float aTimeLength, eGunStates::Enum aStateType) : GunStateBase(aGunStateMachine)
{
	myPriority = aPriority;
	myTimeLength = aTimeLength;
	myStateType = aStateType;
	myLifeTimer = 0.f;
}

void GSM_GenericTransitionState::Enter()
{
	myLifeTimer = 0.f;
}

GunStateBase::eStateTransitionJump GSM_GenericTransitionState::Update(float aDeltaTime)
{
	myLifeTimer += aDeltaTime;
	if (myLifeTimer >= myTimeLength)
	{
		return Single;
	}
	return None;
}

void GSM_GenericTransitionState::Exit()
{
}
