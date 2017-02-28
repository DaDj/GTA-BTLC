#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class  CTaskSimpleSitIdle : public CTaskSimple {
protected:
    CTaskSimpleSitIdle(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleSitIdle, 0x);