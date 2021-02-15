#include "CUtrax.h"

CUtrax &UtraxThreadDesc = *(CUtrax*)0xB6B970;

char CUtrax::startUtraxThread(int a2)
{
	return ((char(__fastcall *)(CUtrax*, int))0x4F4BA0)(this, a2);
}

char CUtrax::loadUtrax()
{
	return ((char(__thiscall *)(CUtrax*))0x4F35B0)(this);
}
