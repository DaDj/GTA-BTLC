#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexReactToAttack : public CTaskComplex {
protected:
    CTaskComplexReactToAttack(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexReactToAttack, 0x);