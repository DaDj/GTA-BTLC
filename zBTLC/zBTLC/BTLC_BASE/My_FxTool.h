#pragma once

#include "../game_sa/common.h"
#include "../Patch/calling.hpp"
#include "other_shared.h"
#include "../Patch/MemoryMgr.h"
#include "../Events_SA/Events_SA.h"
#include "../game_sa/CMenuManager.h"
#include "../game_sa/CRadar.h"
#include "../game_sa/CWorld.h"
#include "../game_sa/RenderWare.h"
#include "../game_sa/FxSystem_c.h"
#include "../game_sa/FxManager_c.h"



namespace My_FxTool
{
	struct My_Effectnames
	{
	
		char mName[24];
	};

	struct My_FxState
	{
		FxSystemBP_c *m_pFxSystem;
		My_Effectnames Objectnamelist[200];
	};
	
	void init();
	void UpdateFxSystem();
	static My_FxState My_State;
}