
#include "My_FxTool.h"
#include "../Events_SA/Events_SA.h"
#include "../game_sa/CTaskComplexPlayHandSignalAnim.h"
#include "../game_sa/CFont.h"
#include "../game_sa/CHud.h"

namespace My_FxTool
{
	using namespace plugin;
	void init()
	{
		Events::initGameEvent += []()
		{
			int numsys = g_fxMan.m_fxSystemBPList.count;
			FxSystemBP_c *CurrentBlueprint = (FxSystemBP_c*)g_fxMan.m_fxSystemBPList.last;
			int i = 0;
		//	My_State.Objectnamelist[i] = CurrentBlueprint->m_nNameKey;
		//	CurrentBlueprint->m_emittersList;

				while (1)
				{
					break;

				}

		};


		Events::gameProcessEvent += []()
		{
			CPed* Player = FindPlayerPed();

			if (KeyPressed('R'))
			{
				char string[40];
				Player->m_pIntelligence->m_TaskMgr.SetTaskSecondary(new CTaskComplexPlayHandSignalAnim(320, 4.0f), 4);
				CFont::SetColor(CRGBA::CRGBA(200, 200, 200, 255));
				sprintf(string, " HAA!");
				CFont::SetFontStyle(FONT_SUBTITLES);
				CFont::SetAlignment(ALIGN_LEFT);
				CFont::SetOutlinePosition(1);
				CFont::SetScale(CHud::x_fac(0.25f), CHud::y_fac(0.5f));
				CFont::PrintString(CHud::x_fac(15.0f), CHud::y_fac(5.0f), string);
			}
		};

		Events::drawRadarOverlayEvent += []()
		{

		};

		Events::drawHudEvent += []
		{
		

		};


	}

	void UpdateFxSystem()
	{
	}

	
}