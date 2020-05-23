#include "CTaskSimplePlayerOnFoot.h"

CTaskSimplePlayerOnFoot::CTaskSimplePlayerOnFoot() : CTaskSimple(plugin::dummy)
{
	plugin::CallMethod<0x685750, CTaskSimplePlayerOnFoot*>(this);
}

void CTaskSimplePlayerOnFoot::ProcessPlayerWeapon(CPlayerPed *playa)
{
	((void(__thiscall *)(CTaskSimplePlayerOnFoot*, CPlayerPed*))0x533ED0)(this, playa);
}