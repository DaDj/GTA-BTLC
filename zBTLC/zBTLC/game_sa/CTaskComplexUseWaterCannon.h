#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexUseWaterCannon : public CTaskComplex {
protected:
    CTaskComplexUseWaterCannon(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexUseWaterCannon, 0x);