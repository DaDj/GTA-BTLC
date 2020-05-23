#include "CTaskSimpleFight.h"

CTaskSimpleFight::CTaskSimpleFight(CEntity *pTargetEntity, int nCommand, unsigned int nIdlePeriod)
	: CTaskSimple(plugin::dummy)
{
	plugin::CallMethod<0x61C470, CTaskSimpleFight*, CEntity*, int, unsigned int>(this, pTargetEntity, nCommand, nIdlePeriod);
}