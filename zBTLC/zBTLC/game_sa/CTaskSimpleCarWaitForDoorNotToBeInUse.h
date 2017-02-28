#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleCarWaitForDoorNotToBeInUse : public CTaskSimple {
protected:
    CTaskSimpleCarWaitForDoorNotToBeInUse(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleCarWaitForDoorNotToBeInUse, 0x);