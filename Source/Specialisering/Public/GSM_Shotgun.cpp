#include "GSM_Shotgun.h"

#include "GSM_GenericTransitionState.h"
#include "GSM_SG_QuickAttack.h"
#include "GSM_SG_Harpoon.h"
#include "GSM_SG_GoopLob.h"

GSM_Shotgun::GSM_Shotgun() : GunStateMachineBase()
{
	myCachedStates[eGunStates::QuickAttack] = 
	{ 
		new GSM_SG_QuickAttack(this, 0),
		new GSM_GenericTransitionState(this, 3, 1.25f, eGunStates::QuickAttack)
	};

	myCachedStates[eGunStates::SG_Harpoon] =
	{
		new GSM_GenericTransitionState(this, 1, 0.55f, eGunStates::SG_Harpoon),
		new GSM_SG_Harpoon(this, 0),
		new GSM_GenericTransitionState(this, 4, 2.f, eGunStates::SG_Harpoon)
	};

	myCachedStates[eGunStates::SG_GoopLob] =
	{
		new GSM_GenericTransitionState(this, 1, 0.83f, eGunStates::SG_GoopLob),
		new GSM_SG_GoopLob(this, 0),
		new GSM_GenericTransitionState(this, 4, 0.5f, eGunStates::SG_GoopLob)
	};

	myActiveState = myCachedStates[eGunStates::QuickAttack][myIndexInStateChain];

	/*myInputStringToStateEnumLUT.emplace(std::string({ static_cast<char>(eInputStringTypes::UPZRIGHT), static_cast<char>(eInputStringTypes::DOWN) }), eGunStates::SG_Harpoon);
	myInputStringToStateEnumLUT.emplace(std::string({ static_cast<char>(eInputStringTypes::UPZLEFT) }), eGunStates::SG_Harpoon);*/
	myInputStringToStateEnumLUT.emplace(std::string({ static_cast<char>(eInputStringTypes::UP) }), eGunStates::SG_Harpoon);

	myInputStringToStateEnumLUT.emplace(std::string({ static_cast<char>(eInputStringTypes::UPZRIGHT) }), eGunStates::SG_GoopLob);
}
