#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"

class CTaskInteriorSitAtDesk : public CTaskSimple {
protected:
    CTaskInteriorSitAtDesk(plugin::dummy_func_t a) : CTaskSimple(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskInteriorSitAtDesk, 0x);