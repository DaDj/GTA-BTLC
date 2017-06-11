//playersprint_armed
//Patch<const char*>(&animationStyles[60].namesPtr[2], "playersprint_armed");
//
//CAnimationStyleDescriptor*	animationStyles;
//animationStyles = (CAnimationStyleDescriptor*)0x8AA5A8;

#include "CAnimationManager.h"
#include "../Patch/MemoryMgr.h"

CAnimationStyleDescriptor *animationStyles = (CAnimationStyleDescriptor*)0x8AA5A8;

void CAnimationStyleDescriptor::My_init()
{
	MemoryVP::Patch<const char*>(&animationStyles[60].namesPtr[2], "sprint_armed");
}