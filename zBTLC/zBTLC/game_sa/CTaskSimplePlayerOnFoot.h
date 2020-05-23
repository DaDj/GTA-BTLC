#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"
#include "CPlayerPed.h"


class  CTaskSimplePlayerOnFoot : public CTaskSimple {
protected:
	CTaskSimplePlayerOnFoot(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
	int m_nAnimationBlockIndex;
	unsigned int m_nFrameCounter;
	int m_nTimer;
	int dword_14; // always 0
	int dword_18; // always 0

	CTaskSimplePlayerOnFoot();
	void  ProcessPlayerWeapon(CPlayerPed *Player);

};


//VALIDATE_SIZE(CTaskSimplePlayerOnFoot, 0x);