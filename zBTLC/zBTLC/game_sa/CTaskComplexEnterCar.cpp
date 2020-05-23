#include "CTaskComplexEnterCar.h"

CTaskComplexEnterCar::CTaskComplexEnterCar(CVehicle* pTargetVehicle, bool bAsDriver, bool bQuitAfterOpeningDoor,
	bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff) : CTaskComplex(plugin::dummy)
{
	plugin::CallMethod<0x63A220, CTaskComplexEnterCar*, CVehicle*, bool, bool, bool, bool>
		(this, pTargetVehicle, bAsDriver, bQuitAfterOpeningDoor, bQuitAfterDraggingPedOut, bCarryOnAfterFallingOff);
}