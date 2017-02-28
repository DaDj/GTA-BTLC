#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexSignalAtPed : public CTaskComplex {
protected:
    CTaskComplexSignalAtPed(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexSignalAtPed, 0x);