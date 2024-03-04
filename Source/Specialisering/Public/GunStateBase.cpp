#include "GunStateBase.h"
#include "GunStateMachineBase.h"

GunStateBase::GunStateBase(GunStateMachineBase* aGunStateMachine) : 
	myStateMachine(aGunStateMachine)
{
}
