#include "CTaskComplexClimb.h"
CTaskComplexClimb::CTaskComplexClimb() : CTaskComplexJump(plugin::dummy)
{
	plugin::CallMethod<0x46A630, CTaskComplexClimb*>(this);
}
