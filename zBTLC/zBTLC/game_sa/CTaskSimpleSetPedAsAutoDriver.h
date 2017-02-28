#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleSetPedAsAutoDriver : public CTaskSimple {
protected:
    CTaskSimpleSetPedAsAutoDriver(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleSetPedAsAutoDriver, 0x);