#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplexJump.h"


class  CTaskComplexClimb : public CTaskComplexJump {
protected:
	CTaskComplexClimb(plugin::dummy_func_t a) : CTaskComplexJump(a) {}
public:

	CTaskComplexClimb();
};


//VALIDATE_SIZE(CTaskComplexClimb, 0x);