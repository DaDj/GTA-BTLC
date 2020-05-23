#include "CTaskSimpleInAir.h"



CTaskSimpleInAir::CTaskSimpleInAir(bool bUsingJumpGlide, bool bUsingFallGlide, bool bUsingClimbJump)
	: CTaskSimple(plugin::dummy), m_timer(plugin::dummy)
{
	plugin::CallMethod<0x678CD0, CTaskSimpleInAir*, bool, bool, bool>
		(this, bUsingJumpGlide, bUsingFallGlide, bUsingClimbJump);
}