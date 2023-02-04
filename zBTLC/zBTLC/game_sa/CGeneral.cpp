#include "CGeneral.h"

float CGeneral::GetATanOfXY(float x, float y)
{
	return ((float (__cdecl *)(float, float))0x53CC70)(x, y);
}


uint16 CGeneral::GetRandomNumber()
{
	static_assert(RAND_MAX == 0x7FFF, "PC-generated random numbers should not exceed 32767");
#ifdef BETTER_RNG
	static_assert(false, "PC-generated random numbers should not exceed 32767");
#else
	return rand();
#endif
}
