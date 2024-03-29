#include "GunStateMachineBase.h"
#include "GunBase.h"

GunStateMachineBase::GunStateMachineBase()
{
	myIndexInStateChain = 0;
	myActiveStateChain = eGunStates::QuickAttack;
}

GunStateMachineBase::~GunStateMachineBase()
{
	myActiveState = nullptr;
	for (auto& states : myCachedStates)
	{
		for (auto& state : states)
		{
			delete state;
		}
	}
}

void GunStateMachineBase::Init(AGunBase* aGunActor)
{
	myGunActor = aGunActor;
}

void GunStateMachineBase::Update(float aDeltaTime)
{
	AdvanceStateTransitionChain(myActiveState->Update(aDeltaTime));
}

void GunStateMachineBase::AdvanceStateTransitionChain(int aTransitionJumpLength)
{
	if (aTransitionJumpLength == 0)
	{
		return;
	}

	int newStateChainIndex = myIndexInStateChain + aTransitionJumpLength;
	if (newStateChainIndex >= myCachedStates[myActiveStateChain].size())
	{
		ForceStateChange(eGunStates::QuickAttack);
		return;
	}

	myActiveState->Exit();
	myIndexInStateChain = newStateChainIndex;
	myActiveState = myCachedStates[myActiveStateChain][myIndexInStateChain];
	myActiveState->Enter();
}

void GunStateMachineBase::RequestStateChangeString(const std::string aInputString)
{
	auto didFind = myInputStringToStateEnumLUT.find(aInputString);
	if (didFind != myInputStringToStateEnumLUT.end())
	{
		RequestStateChangeEnum(didFind->second);
	}
}

void GunStateMachineBase::RequestStateChangeEnum(eGunStates::Enum aGunState)
{
	GunStateBase* newState = myCachedStates[aGunState][0];
	if (myActiveState->GetPriority() <= newState->GetPriority())
	{
		myActiveState->Exit();
		myActiveState = newState;
		myActiveStateChain = aGunState;
		myIndexInStateChain = 0;
		myActiveState->Enter();
	}
}

void GunStateMachineBase::ForceStateChange(eGunStates::Enum aGunState)
{
	GunStateBase* newState = myCachedStates[aGunState][0];

	myActiveState->Exit();
	myActiveState = newState;
	myActiveStateChain = aGunState;
	myIndexInStateChain = 0;
	myActiveState->Enter();
}

void GunStateMachineBase::SendMouseInput()
{
	myActiveState->SendMouseInput();
}

void GunStateMachineBase::Shoot(int aProjectileID)
{
	myGunActor->Shoot(aProjectileID);
}
