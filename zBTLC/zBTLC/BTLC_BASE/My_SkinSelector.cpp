#include "My_SkinSelector.h"
#include "debug.h"


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
			DebugMenuEntry *e = DebugMenuAddVar("BTLC", "Set Skin", &current_index, Set_skin , 1, 0, NumPeds, NULL);
			DebugMenuEntrySetWrap(e, true);

			DebugMenuAddCmd("BTLC", "Set Skin to Player", []() {Set_SkintoIndex(0); });
			DebugMenuAddCmd("BTLC", "Set Skin to CluckinBell", []() {Set_SkintoIndex(154); });
		};

	}

	void Set_SkintoIndex(int index)
	{
		current_index = index;
		Set_skin();
	}

	void Set_skin()
	{
		CPed *playa = FindPlayerPed();

			if (playa && playa->IsAlive())
			{
				((CPlayerPed*)FindPlayerPed())->GetPadFromPlayer()->DisablePlayerControls = 1;
				CStreaming::RequestModel(PedModel[current_index], 2);
				CStreaming::LoadAllRequestedModels(false);
				unsigned int savedAnimGroup = playa->m_dwAnimGroup;
				playa->DeleteRwObject();
				playa->m_wModelIndex = -1;
				playa->SetModelIndex(PedModel[current_index]);
				playa->m_wModelIndex = PedModel[current_index];
				playa->m_dwAnimGroup = savedAnimGroup;

				CStreaming::SetModelIsDeletable(PedModel[current_index]);
				((CPlayerPed*)FindPlayerPed())->GetPadFromPlayer()->DisablePlayerControls = 0;
			}
	}
}