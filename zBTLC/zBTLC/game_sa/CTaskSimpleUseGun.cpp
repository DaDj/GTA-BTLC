#include "CTaskSimpleUseGun.h"


CTaskSimpleUseGun::CTaskSimpleUseGun(CEntity *pTargetEntity, CVector vecTarget, unsigned char nCommand,
	unsigned short nBurstLength, bool bAimImmediate) : CTaskSimple(plugin::dummy)
{
	plugin::CallMethod<0x61DE60, CTaskSimpleUseGun*, CEntity*, CVector, unsigned char, unsigned short, bool>
		(this, pTargetEntity, vecTarget, nCommand, nBurstLength, bAimImmediate);
}