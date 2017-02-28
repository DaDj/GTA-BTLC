#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleStandStill.h"

class CTaskSimpleOnEscalator : public CTaskSimpleStandStill {
protected:
    CTaskSimpleOnEscalator(plugin::dummy_func_t a) : CTaskSimpleStandStill(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleOnEscalator, 0x);