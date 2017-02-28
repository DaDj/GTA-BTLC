#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexHitByGunResponse : public CTaskComplex {
protected:
    CTaskComplexHitByGunResponse(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexHitByGunResponse, 0x);