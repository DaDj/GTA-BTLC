#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexStuckInAir : public CTaskComplex {
protected:
    CTaskComplexStuckInAir(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexStuckInAir, 0x);