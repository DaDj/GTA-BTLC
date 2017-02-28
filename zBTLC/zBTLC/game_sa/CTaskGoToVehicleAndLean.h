#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskGoToVehicleAndLean : public CTaskComplex {
protected:
    CTaskGoToVehicleAndLean(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskGoToVehicleAndLean, 0x);