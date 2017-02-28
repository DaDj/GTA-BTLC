#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleUninterruptable : public CTaskSimple {
protected:
    CTaskSimpleUninterruptable(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleUninterruptable, 0x);