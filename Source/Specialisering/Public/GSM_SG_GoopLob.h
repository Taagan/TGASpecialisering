#pragma once
#include "GunStateBase.h"

class GSM_SG_GoopLob : public GunStateBase
{
public:
	GSM_SG_GoopLob() = delete;
	GSM_SG_GoopLob(GunStateMachineBase* aGunStateMachine, int aPriority);
	virtual ~GSM_SG_GoopLob() = default;

	virtual void Enter() override;
	virtual eStateTransitionJump Update(float aDeltaTime) override;
	virtual void Exit() override;

private:
};