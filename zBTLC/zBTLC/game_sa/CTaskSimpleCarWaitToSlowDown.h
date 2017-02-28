#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleCarWaitToSlowDown : public CTaskSimple {
protected:
    CTaskSimpleCarWaitToSlowDown(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleCarWaitToSlowDown, 0x);