#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexUsePairedAttractor : public CTaskComplex {
protected:
    CTaskComplexUsePairedAttractor(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexUsePairedAttractor, 0x);