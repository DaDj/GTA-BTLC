#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleBeHitWhileMoving : public CTaskSimple {
protected:
    CTaskSimpleBeHitWhileMoving(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleBeHitWhileMoving, 0x);