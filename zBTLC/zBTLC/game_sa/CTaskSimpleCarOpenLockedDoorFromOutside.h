#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleCarOpenLockedDoorFromOutside : public CTaskSimple {
protected:
    CTaskSimpleCarOpenLockedDoorFromOutside(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleCarOpenLockedDoorFromOutside, 0x);