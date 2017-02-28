#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexEvasiveStep : public CTaskComplex {
protected:
    CTaskComplexEvasiveStep(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexEvasiveStep, 0x);