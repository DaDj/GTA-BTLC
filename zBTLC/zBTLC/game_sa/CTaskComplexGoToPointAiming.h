#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexGoToPointAiming : public CTaskComplex {
protected:
    CTaskComplexGoToPointAiming(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexGoToPointAiming, 0x);