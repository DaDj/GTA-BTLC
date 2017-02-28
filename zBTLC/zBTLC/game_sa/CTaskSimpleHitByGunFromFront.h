#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleRunAnim.h"

class CTaskSimpleHitByGunFromFront : public CTaskSimpleRunAnim {
protected:
    CTaskSimpleHitByGunFromFront(plugin::dummy_func_t a) : CTaskSimpleRunAnim(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleHitByGunFromFront, 0x);