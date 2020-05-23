#include "CTaskSimpleSwim.h"

CTaskSimpleSwim::CTaskSimpleSwim(CVector const* pPosn, CPed* pPed) : CTaskSimple(plugin::dummy)
{
	plugin::CallMethod<0x688930, CTaskSimpleSwim*, CVector const*, CPed*>(this, pPosn, pPed);
}