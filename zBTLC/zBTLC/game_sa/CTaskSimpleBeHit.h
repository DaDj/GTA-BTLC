#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleBeHit : public CTaskSimple {
protected:
    CTaskSimpleBeHit(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleBeHit, 0x);