#pragma once
#include "GunStateBase.h"

class GSM_SG_QuickAttack : public GunStateBase
{
public:
	GSM_SG_QuickAttack() = delete;
	GSM_SG_QuickAttack(GunStateMachineBase* aGunStateMachine, int aPriority);
	virtual ~GSM_SG_QuickAttack() = default;

	virtual void Enter() override;
	virtual eStateTransitionJump Update(float aDeltaTime) override;
	virtual void Exit() override;

private:
};