#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleRunTimedAnim.h"

class CTaskSimpleHandsUp : public CTaskSimpleRunTimedAnim {
protected:
    CTaskSimpleHandsUp(plugin::dummy_func_t a) : CTaskSimpleRunTimedAnim(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleHandsUp, 0x);