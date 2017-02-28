#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleSetKindaStayInSamePlace : public CTaskSimple {
protected:
    CTaskSimpleSetKindaStayInSamePlace(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleSetKindaStayInSamePlace, 0x);