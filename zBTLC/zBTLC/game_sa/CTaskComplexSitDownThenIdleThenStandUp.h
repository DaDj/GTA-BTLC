#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexSitDownThenIdleThenStandUp : public CTaskComplex {
protected:
    CTaskComplexSitDownThenIdleThenStandUp(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexSitDownThenIdleThenStandUp, 0x);