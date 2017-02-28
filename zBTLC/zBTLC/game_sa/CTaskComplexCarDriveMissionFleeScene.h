#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskComplexCarDriveMission.h"

class CTaskComplexCarDriveMissionFleeScene : public CTaskComplexCarDriveMission {
protected:
    CTaskComplexCarDriveMissionFleeScene(plugin::dummy_func_t a) : CTaskComplexCarDriveMission(a) {}
public:
    
};

//VALIDATE_SIZE(CTaskComplexCarDriveMissionFleeScene, 0x);