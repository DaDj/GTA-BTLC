#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleRunAnim.h"

class CTaskSimpleHitByGunFromLeft : public CTaskSimpleRunAnim {
protected:
    CTaskSimpleHitByGunFromLeft(plugin::dummy_func_t a) : CTaskSimpleRunAnim(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleHitByGunFromLeft, 0x);