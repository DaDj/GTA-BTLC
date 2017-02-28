#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexLeaveCarAndWander : public CTaskComplex {
protected:
    CTaskComplexLeaveCarAndWander(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexLeaveCarAndWander, 0x);