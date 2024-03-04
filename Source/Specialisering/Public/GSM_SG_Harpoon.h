#pragma once
#include "GunStateBase.h"

class GSM_SG_Harpoon : public GunStateBase
{
public:
	GSM_SG_Harpoon() = delete;
	GSM_SG_Harpoon(GunStateMachineBase* aGunStateMachine, int aPriority);
	virtual ~GSM_SG_Harpoon() = default; 

	virtual void Enter() override;
	virtual eStateTransitionJump Update(float aDeltaTime) override;
	virtual void Exit() override;

private:
};