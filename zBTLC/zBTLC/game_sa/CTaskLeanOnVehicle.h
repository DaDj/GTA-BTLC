#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskLeanOnVehicle : public CTaskSimple {
protected:
    CTaskLeanOnVehicle(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskLeanOnVehicle, 0x);