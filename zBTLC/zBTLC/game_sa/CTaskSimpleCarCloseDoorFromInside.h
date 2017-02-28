#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleCarCloseDoorFromInside : public CTaskSimple {
protected:
    CTaskSimpleCarCloseDoorFromInside(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleCarCloseDoorFromInside, 0x);