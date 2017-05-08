#pragma once
#include "../game_sa/CVector.h"
#include "../game_sa/CCam.h"
#include "../game_sa/common.h"
#include "../Patch/calling.hpp"
#include "other_shared.h"
#include "../Patch/MemoryMgr.h"
namespace My_CCam
{
	static CVector offset;
	static void _fastcall Process_AimWeapon(CCam *cam, int, CVector const &vec, float arg3, float arg4, float arg5);
	void INIT();
}