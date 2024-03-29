#include "GSM_SG_QuickAttack.h"
#include "GunStateMachineBase.h"

GSM_SG_QuickAttack::GSM_SG_QuickAttack(GunStateMachineBase* aGunStateMachine, int aPriority) : GunStateBase(aGunStateMachine)
{
	myPriority = aPriority;
}

void GSM_SG_QuickAttack::Enter()
{
	myHasReceivedInputThisFrame = false;
}

GunStateBase::eStateTransitionJump GSM_SG_QuickAttack::Update(float aDeltaTime)
{
	if (myHasReceivedInputThisFrame)
	{
		myStateMachine->Shoot(0);
		return Single;
	}

	myHasReceivedInputThisFrame = false;
	return None;
}

void GSM_SG_QuickAttack::Exit()
{
}
