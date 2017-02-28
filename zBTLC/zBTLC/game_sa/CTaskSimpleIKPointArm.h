#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleIKChain.h"

class CTaskSimpleIKPointArm : public CTaskSimpleIKChain {
protected:
    CTaskSimpleIKPointArm(plugin::dummy_func_t a) : CTaskSimpleIKChain(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleIKPointArm, 0x);