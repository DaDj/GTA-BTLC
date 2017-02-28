#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimpleWaitUntilAreaCodesMatch.h"

class CTaskSimpleWaitUntilLeaderAreaCodesMatch : public CTaskSimpleWaitUntilAreaCodesMatch {
protected:
    CTaskSimpleWaitUntilLeaderAreaCodesMatch(plugin::dummy_func_t a) : CTaskSimpleWaitUntilAreaCodesMatch(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskSimpleWaitUntilLeaderAreaCodesMatch, 0x);