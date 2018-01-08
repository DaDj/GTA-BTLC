#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"
#include "CTaskTimer.h"

class CTaskComplexKillPedOnFoot : public CTaskComplex {
protected:
    CTaskComplexKillPedOnFoot(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
	unsigned char   m_nFlags;
	class CPed       *m_pTarget;
	unsigned int  m_dwAttackFlags;
	unsigned int  m_dwActionDelay;
	unsigned int  m_dwActionChance;
	char field_20;
	unsigned int  m_dwLaunchTime;
	signed int    m_dwTime;
    CTaskTimer        m_taskTimer;

	CTaskComplexKillPedOnFoot();
};

VALIDATE_SIZE(CTaskComplexKillPedOnFoot, 0x38);