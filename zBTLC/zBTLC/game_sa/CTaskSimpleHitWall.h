#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleRunAnim.h"

class CTaskSimpleHitWall : public CTaskSimpleRunAnim {
protected:
    CTaskSimpleHitWall(plugin::dummy_func_t a) : CTaskSimpleRunAnim(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleHitWall, 0x);