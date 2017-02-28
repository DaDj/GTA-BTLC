#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleCarGoToPointNearDoorUntilDoorNotInUse : public CTaskSimple {
protected:
    CTaskSimpleCarGoToPointNearDoorUntilDoorNotInUse(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleCarGoToPointNearDoorUntilDoorNotInUse, 0x);