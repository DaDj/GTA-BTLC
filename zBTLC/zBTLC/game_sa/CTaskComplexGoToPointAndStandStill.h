#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexGoToPointAndStandStill : public CTaskComplex {
protected:
    CTaskComplexGoToPointAndStandStill(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexGoToPointAndStandStill, 0x);