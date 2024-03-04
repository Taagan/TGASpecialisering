#pragma once
#include "GunStateBase.h"
#include "GunStates.h"

class GSM_GenericTransitionState : public GunStateBase
{
public:
	GSM_GenericTransitionState() = delete;
	GSM_GenericTransitionState(GunStateMachineBase* aGunStateMachine, int aPriority, float aTimeLength, eGunStates::Enum aStateType);
	virtual ~GSM_GenericTransitionState() = default;

	virtual void Enter() override;
	virtual eStateTransitionJump Update(float aDeltaTime) override;
	virtual void Exit() override;

private: 
	eGunStates::Enum myStateType;
	float myTimeLength;
	float myLifeTimer;
};