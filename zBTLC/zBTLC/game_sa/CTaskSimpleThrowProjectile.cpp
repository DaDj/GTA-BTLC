#include "CTaskSimpleThrowProjectile.h"


CTaskSimpleThrowProjectile::CTaskSimpleThrowProjectile(CEntity* pTarget, CVector Posn) : CTaskSimple(plugin::dummy)
{
	plugin::CallMethod<0x61F660, CTaskSimpleThrowProjectile*, CEntity*, CVector>(this, pTarget, Posn);
}