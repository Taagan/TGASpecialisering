#include "GSM_SG_GoopLob.h"
#include "GunStateMachineBase.h"

GSM_SG_GoopLob::GSM_SG_GoopLob(GunStateMachineBase* aGunStateMachine, int aPriority) : GunStateBase(aGunStateMachine)
{
	myPriority = aPriority;
}

void GSM_SG_GoopLob::Enter()
{
	myHasReceivedInputThisFrame = false;
}

GunStateBase::eStateTransitionJump GSM_SG_GoopLob::Update(float aDeltaTime)
{
	if (myHasReceivedInputThisFrame)
	{
		myStateMachine->Shoot(2);
		return Single;
	}

	myHasReceivedInputThisFrame = false;
	return None;
}

void GSM_SG_GoopLob::Exit()
{
}
