#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleEvasiveStep : public CTaskSimple {
protected:
    CTaskSimpleEvasiveStep(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleEvasiveStep, 0x);