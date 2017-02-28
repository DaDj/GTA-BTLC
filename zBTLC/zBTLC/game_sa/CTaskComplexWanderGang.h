#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplexWander.h"

class CTaskComplexWanderGang : public CTaskComplexWander {
protected:
    CTaskComplexWanderGang(plugin::dummy_func_t a) : CTaskComplexWander(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexWanderGang, 0x);