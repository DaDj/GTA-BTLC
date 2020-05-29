#include "My_SkinSelector.h"



using namespace plugin;
namespace My_SkinSelector
{


	static int PedModel[600];
	static int NumPeds = 0;
	static bool isActive = false;
	static int keyPressTime = 500;
	static int current_index = 0;

	void Init()
	{
		Events::initGameEvent += []()
		{

			for (int i = 0; i < 20000; i++)
			{
				if (CModelInfo::ms_modelInfoPtrs[i] && CModelInfo::ms_modelInfoPtrs[i]->GetModelType() == MODEL_INFO_PED
					&& ((CPedModelInfo*)CModelInfo::ms_modelInfoPtrs[i])->m_nStatType != 41)
				{
					PedModel[NumPeds] = i;
					NumPeds++;
				}
			}
		};

		Events::gameProcessEvent += []
		{
			if (KeyPressed(VK_MENU) && KeyPressed('Y') && CTimer::m_snTimeInMilliseconds - keyPressTime > 500)
			{
				isActive = !isActive;
				keyPressTime = CTimer::m_snTimeInMilliseconds;
			}

			if (isActive)
			{
				CPed *playa = FindPlayerPed();

				

				if ((KeyPressed('Y') ||  KeyPressed('X')) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500)
				{
					keyPressTime = CTimer::m_snTimeInMilliseconds;
					if (KeyPressed('Y'))
					{
						if (current_index == 0)
							current_index = NumPeds;
						else
							current_index--;
					}
					if (KeyPressed('X'))
					{
						if (current_index == NumPeds)
							current_index = 0;
						else
							current_index++;
					}


					if (playa && playa->IsAlive())
					{
						CStreaming::RequestModel(PedModel[current_index], 2);
						CStreaming::LoadAllRequestedModels(false);
						unsigned int savedAnimGroup = playa->m_dwAnimGroup;
						playa->DeleteRwObject();
						playa->m_wModelIndex = -1;
						playa->SetModelIndex(PedModel[current_index]);
						playa->m_wModelIndex = PedModel[current_index];
						
						playa->m_dwAnimGroup = savedAnimGroup;

						CStreaming::SetModelIsDeletable(PedModel[current_index]);
					}
				}		
			}
		};

	}
}