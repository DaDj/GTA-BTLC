#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplexEnterCar.h"

class CTaskComplexDragPedFromCar : public CTaskComplexEnterCar {
protected:
    CTaskComplexDragPedFromCar(plugin::dummy_func_t a) : CTaskComplexEnterCar(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexDragPedFromCar, 0x);