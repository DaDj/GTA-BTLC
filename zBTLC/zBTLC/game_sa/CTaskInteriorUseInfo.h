#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskInteriorUseInfo : public CTaskComplex {
protected:
    CTaskInteriorUseInfo(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskInteriorUseInfo, 0x);