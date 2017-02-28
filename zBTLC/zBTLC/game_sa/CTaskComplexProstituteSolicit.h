#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexProstituteSolicit : public CTaskComplex {
protected:
    CTaskComplexProstituteSolicit(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexProstituteSolicit, 0x);