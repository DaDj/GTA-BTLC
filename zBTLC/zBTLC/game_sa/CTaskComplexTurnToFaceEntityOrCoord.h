#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplex.h"

class CTaskComplexTurnToFaceEntityOrCoord : public CTaskComplex {
protected:
    CTaskComplexTurnToFaceEntityOrCoord(plugin::dummy_func_t a) : CTaskComplex(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexTurnToFaceEntityOrCoord, 0x);