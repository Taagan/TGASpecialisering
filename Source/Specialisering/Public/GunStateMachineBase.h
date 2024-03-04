#pragma once
#include "GunStateBase.h"
#include <vector>
#include <array>
#include <unordered_map>
#include <string>
#include "GunStates.h"

class AGunBase;

class GunStateMachineBase
{
public:
	GunStateMachineBase();
	virtual ~GunStateMachineBase();

	void Init(AGunBase* aGunActor);
	void Update(float aDeltaTime);

	void AdvanceStateTransitionChain(int aTransitionJumpLength);

	void RequestStateChangeEnum(eGunStates::Enum aGunState);
	void RequestStateChangeString(const std::string& aInputString);
	void ForceStateChange(eGunStates::Enum aGunState);

	void SendMouseInput();

	void Shoot();

private:
protected:
	AGunBase* myGunActor;

	std::unordered_map<std::string, eGunStates::Enum> myInputStringToStateEnumLUT;
	std::array<std::vector<GunStateBase*>, eGunStates::Count> myCachedStates;
	GunStateBase* myActiveState;
	eGunStates::Enum myActiveStateChain;
	int myIndexInStateChain;

	float mySpecialAttackResourceMaxAmount;
	float mySpecialAttackResource;
	float mySpecialAttackPercentRequired;
};