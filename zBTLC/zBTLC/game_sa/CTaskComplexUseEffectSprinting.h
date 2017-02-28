#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplexUseEffect.h"

class CTaskComplexUseEffectSprinting : public CTaskComplexUseEffect {
protected:
    CTaskComplexUseEffectSprinting(plugin::dummy_func_t a) : CTaskComplexUseEffect(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexUseEffectSprinting, 0x);