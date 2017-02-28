#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplexSmartFleeEntity.h"

class CTaskComplexFleeShooting : public CTaskComplexSmartFleeEntity {
protected:
    CTaskComplexFleeShooting(plugin::dummy_func_t a) : CTaskComplexSmartFleeEntity(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexFleeShooting, 0x);