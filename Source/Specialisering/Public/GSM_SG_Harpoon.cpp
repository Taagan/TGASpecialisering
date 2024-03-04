#include "GSM_SG_Harpoon.h"
#include "GunStateMachineBase.h"

GSM_SG_Harpoon::GSM_SG_Harpoon(GunStateMachineBase* aGunStateMachine, int aPriority) : GunStateBase(aGunStateMachine)
{
	myPriority = aPriority;
}

void GSM_SG_Harpoon::Enter()
{
	myHasReceivedInputThisFrame = false;
}

GunStateBase::eStateTransitionJump GSM_SG_Harpoon::Update(float aDeltaTime)
{
	if (myHasReceivedInputThisFrame)
	{
		myStateMachine->Shoot();
		return Single;
	}

	myHasReceivedInputThisFrame = false;
	return None;
}

void GSM_SG_Harpoon::Exit()
{
}
