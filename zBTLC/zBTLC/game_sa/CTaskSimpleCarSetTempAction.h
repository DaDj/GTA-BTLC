#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleCarDrive.h"

class CTaskSimpleCarSetTempAction : public CTaskSimpleCarDrive {
protected:
    CTaskSimpleCarSetTempAction(plugin::dummy_func_t a) : CTaskSimpleCarDrive(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleCarSetTempAction, 0x);