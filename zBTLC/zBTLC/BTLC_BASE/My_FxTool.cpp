
#include "My_FxTool.h"
#include "../Events_SA/Events_SA.h"

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