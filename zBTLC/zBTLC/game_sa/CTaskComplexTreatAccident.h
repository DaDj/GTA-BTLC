#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexTreatAccident : public CTaskComplex {
protected:
    CTaskComplexTreatAccident(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexTreatAccident, 0x);