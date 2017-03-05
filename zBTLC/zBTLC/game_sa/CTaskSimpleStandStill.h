#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleStandStill : public CTaskSimple {
protected:
    CTaskSimpleStandStill(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
	CTaskSimpleStandStill(int nTime, char a3, char a4, float a5);
    
};

//VALIDATE_SIZE(CTaskSimpleStandStill, 0x);