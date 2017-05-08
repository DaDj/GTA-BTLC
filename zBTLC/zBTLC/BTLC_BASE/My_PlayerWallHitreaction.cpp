#include "../Events_SA/Events_SA.h"
#include "../game_sa/common.h"
#include "../game_sa/CTaskSimpleHitWall.h"
#include "../game_sa/CWorld.h"
#include "../game_sa/CFont.h"
#include "../game_sa/CTaskSimpleHitWall.h"
#include "../game_sa/CTaskSimpleStandStill.h"
#include "../game_sa/CTask.h"
#include "../game_sa/CPad.h"
#include "../BTLC_BASE/other_shared.h"
#include "../game_sa/CTimer.h"
#include "../game_sa/CCamera.h"
#include "../Patch/calling.hpp"
#include "../Patch/MemoryMgr.h"
#include "My_PlayerWallHitreaction.h"

using namespace plugin;



namespace My_PlayerWallhitreactions
{

	void init()
	{
		plugin::Events::gameProcessEvent += []()
		{
			process();
		};
	}

	void process()
	{
		static bool Wall_inway_test = false;
		static int time_last_hit = 0;
		int time_check;

		if (FindPlayerPed() && !FindPlayerPed()->m_bInVehicle && FindPlayerPed()->IsAlive())
		{
			CVector Position = FindPlayerPed()->TransformFromObjectSpace(CVector(0.0f, 0.6f, 0.6f));
			CVector PlayerPosition = FindPlayerCoors(-1);
			CVector Playerspeed = FindPlayerSpeed(-1);
			CPed* Playa = FindPlayerPed();
			eTaskType activetask = Playa->m_pIntelligence->m_TaskMgr.GetActiveTask()->GetId();
			time_check = CTimer::m_snTimeInMilliseconds - (time_last_hit);
			Wall_inway_test = CWorld::GetIsLineOfSightClear(PlayerPosition, Position, 1, 0, 0, 0, 0, 0, 0);

			if (time_check < 20 && activetask != TASK_COMPLEX_JUMP)
				Playa->m_pIntelligence->m_TaskMgr.ClearTaskEventResponse();

			if (!Wall_inway_test && !CPad::GetPad(0)->GetJump() && activetask != TASK_SIMPLE_USE_GUN
				&& activetask != TASK_COMPLEX_FALL_AND_GET_UP && activetask != TASK_COMPLEX_FALL_AND_STAY_DOWN
				&& activetask != TASK_COMPLEX_CLIMB && activetask != TASK_SIMPLE_CLIMB && activetask != TASK_COMPLEX_JUMP
				&& activetask != TASK_SIMPLE_JUMP && activetask != TASK_SIMPLE_DUCK && activetask != TASK_SIMPLE_FALL)
			{

				if ((abs(Playerspeed.x) >= 0.12 || abs(Playerspeed.y) > 0.12) && time_check > 800)
				{
					Playa->m_pIntelligence->m_TaskMgr.SetTask(new CTaskSimpleHitWall, 1, false);
					time_last_hit = CTimer::m_snTimeInMilliseconds;
				}
				else if (abs(Playerspeed.x) < 0.01  && abs(Playerspeed.y) < 0.01 && CPad::GetPad(0)->GetPedWalkUpDown() && !CPad::GetPad(0)->GetJump() && time_check > 800)
				{
					Playa->m_pIntelligence->m_TaskMgr.SetTask(new CTaskSimpleStandStill(20, 1, 1, 2.0), 2, false);
					time_last_hit = CTimer::m_snTimeInMilliseconds;
				}
			}
		}
	}
}