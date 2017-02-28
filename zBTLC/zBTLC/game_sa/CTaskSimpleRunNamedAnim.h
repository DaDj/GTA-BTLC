#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleAnim.h"

class CTaskSimpleRunNamedAnim : public CTaskSimpleAnim {
protected:
    CTaskSimpleRunNamedAnim(plugin::dummy_func_t a) : CTaskSimpleAnim(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleRunNamedAnim, 0x);