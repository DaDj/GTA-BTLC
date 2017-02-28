#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplexWanderStandard.h"

class CTaskComplexWanderProstitute : public CTaskComplexWanderStandard {
protected:
    CTaskComplexWanderProstitute(plugin::dummy_func_t a) : CTaskComplexWanderStandard(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexWanderProstitute, 0x);