#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleTriggerLookAt : public CTaskSimple {
protected:
    CTaskSimpleTriggerLookAt(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleTriggerLookAt, 0x);