#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTask.h"

class CTaskSimple : public CTask {
    CTaskSimple() = delete;
protected:
    CTaskSimple(plugin::dummy_func_t a) : CTask(a) {}
public:
	virtual bool ProcessPed(class CPed *ped);//=0
	virtual bool SetPedPosition(class CPed *ped);
};

VALIDATE_SIZE(CTaskSimple, 8);