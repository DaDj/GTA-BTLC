#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleAnim.h"

class CTaskSimpleRunTimedAnim : public CTaskSimpleAnim {
protected:
    CTaskSimpleRunTimedAnim(plugin::dummy_func_t a) : CTaskSimpleAnim(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleRunTimedAnim, 0x);