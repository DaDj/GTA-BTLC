#include "CTaskSimpleDuck.h"


CTaskSimpleDuck::CTaskSimpleDuck(eDuckControlTypes DuckControlType, unsigned short nLengthOfDuck, short nUseShotsWhizzingEvents)
	: CTaskSimple(plugin::dummy)
{
	plugin::CallMethod<0x691FC0, CTaskSimpleDuck*, eDuckControlTypes, unsigned short, short>(this, DuckControlType, nLengthOfDuck, nUseShotsWhizzingEvents);
}