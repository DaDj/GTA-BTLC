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

using namespace plugin;

class FEAT_PlayerWallHitreactions {
public:
	

	FEAT_PlayerWallHitreactions() {

		static bool Wall_inway_test = false;

		Events::gameProcessEvent += [] {

			static int time_last_hit = 0;
			int time_check;

			if (FindPlayerPed())
			{	
				CVector Position = FindPlayerPed()->TransformFromObjectSpace(CVector(0.0f, 0.6f, 0.6f));
				CVector PlayerPosition = FindPlayerCoors(-1);
				CVector Playerspeed = FindPlayerSpeed(-1);
				CPed* Playa = FindPlayerPed();
				time_check = CTimer::m_snTimeInMilliseconds - (time_last_hit);

				Wall_inway_test = CWorld::GetIsLineOfSightClear(PlayerPosition, Position, 1, 0, 0, 0, 0, 0, 0);

				eTaskType activetask = Playa->m_pIntelligence->m_TaskMgr.GetActiveTask()->GetId();


				if ( time_check < 20 && activetask != TASK_COMPLEX_JUMP)
				Playa->m_pIntelligence->m_TaskMgr.ClearTaskEventResponse();

		

				if (!Wall_inway_test  && !CPad::GetPad(0)->GetJump() 
					&& activetask != TASK_COMPLEX_FALL_AND_GET_UP && activetask != TASK_COMPLEX_FALL_AND_STAY_DOWN
					&& activetask != TASK_COMPLEX_CLIMB && activetask != TASK_SIMPLE_CLIMB && activetask != TASK_COMPLEX_JUMP
					&& activetask != TASK_SIMPLE_JUMP && activetask != TASK_SIMPLE_DUCK && activetask != TASK_SIMPLE_FALL )
				{
					
					if ((abs(Playerspeed.x) >= 0.12 || abs(Playerspeed.y) > 0.12) && time_check > 800)
					{
						Playa->m_pIntelligence->m_TaskMgr.SetTask(new CTaskSimpleHitWall, 1, false);
						time_last_hit = CTimer::m_snTimeInMilliseconds;
					}
					else if (CPad::GetPad(0)->GetPedWalkUpDown() && !CPad::GetPad(0)->GetJump() &&time_check > 800)
					{
						Playa->m_pIntelligence->m_TaskMgr.SetTask(new CTaskSimpleStandStill(20, 1, 1, 2.0), 2, false);
						time_last_hit = CTimer::m_snTimeInMilliseconds;
					}
				}

			}
		};
		
		Events::drawHudEvent += [] {
			if (!Wall_inway_test)
			{
				CFont::SetColor(CRGBA::CRGBA(200, 200, 200, 255));
				CFont::SetFontStyle(FONT_PRICEDOWN);
				CFont::SetAlignment(ALIGN_CENTER);
				CFont::SetOutlinePosition(1);
				CFont::SetScale(x_fac(0.5f), y_fac(0.5f));
				CFont::PrintString(x_fac(340.0f), y_fac(10.0f), "~w~TEST FALSE");
			}

			if (!FindPlayerPed()->m_bFallenDown)
			{
				CFont::SetColor(CRGBA::CRGBA(200, 200, 200, 255));
				CFont::SetFontStyle(FONT_PRICEDOWN);
				CFont::SetAlignment(ALIGN_CENTER);
				CFont::SetOutlinePosition(1);
				CFont::SetScale(x_fac(0.3f), y_fac(0.4f));
				CFont::PrintString(x_fac(340.0f), y_fac(20.0f), "~w~ducking");

				eTaskType activetask = FindPlayerPed()->m_pIntelligence->m_TaskMgr.GetActiveTask()->GetId();


				char string[40];
				CVector Playerspeed = FindPlayerSpeed(-1);
				sprintf(string, "%f", Playerspeed.x);
				CFont::PrintString(x_fac(100.0f), y_fac(20.0f), string);
				sprintf(string, "%f", Playerspeed.y);
				CFont::PrintString(x_fac(100.0f), y_fac(40.0f), string);
				sprintf(string, "%d", activetask);
				CFont::PrintString(x_fac(100.0f), y_fac(80.0f), string);
			}

		};
	}
} FEAT_PlayerWallHitreactions;
