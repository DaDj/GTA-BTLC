#include "CCamera.h"

CCamera &TheCamera = *(CCamera *)0xB6F028;


float& CCamera::m_f3rdPersonCHairMultY = *(float *)0xB6EC10;
float& CCamera::m_f3rdPersonCHairMultX = *(float *)0xB6EC14;
float& CCamera::m_fMouseAccelVertical = *(float *)0xB6EC18;
float& CCamera::m_fMouseAccelHorzntl = *(float *)0xB6EC1C;


char CCamera::GetFading()
{
 return	((char(__thiscall *)(CCamera *))0x50ADE0)(this);
}

int CCamera::GetFadeStage()
{
 return	((int(__thiscall *)(CCamera *))0x50AE20)(this);
}