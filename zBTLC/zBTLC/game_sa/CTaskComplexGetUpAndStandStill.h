#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexGetUpAndStandStill : public CTaskComplex {
protected:
    CTaskComplexGetUpAndStandStill(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexGetUpAndStandStill, 0x);