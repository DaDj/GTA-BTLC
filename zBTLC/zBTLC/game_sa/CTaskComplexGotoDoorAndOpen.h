#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexGotoDoorAndOpen : public CTaskComplex {
protected:
    CTaskComplexGotoDoorAndOpen(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexGotoDoorAndOpen, 0x);