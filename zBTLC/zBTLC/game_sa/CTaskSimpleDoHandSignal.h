#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleDoHandSignal : public CTaskSimple {
protected:
    CTaskSimpleDoHandSignal(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleDoHandSignal, 0x);