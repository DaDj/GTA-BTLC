#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexLeaveCarAsPassengerWait : public CTaskComplex {
protected:
    CTaskComplexLeaveCarAsPassengerWait(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexLeaveCarAsPassengerWait, 0x);