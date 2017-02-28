#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskSimpleSetStayInSamePlace : public CTaskSimple {
protected:
    CTaskSimpleSetStayInSamePlace(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleSetStayInSamePlace, 0x);