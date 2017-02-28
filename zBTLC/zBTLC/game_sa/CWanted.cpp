#include "CWanted.h"

CWanted* CWanted::FindPlayerWanted(int number)
{
	return ((CWanted* (*__cdecl)(int))0x56E230)(number);
}