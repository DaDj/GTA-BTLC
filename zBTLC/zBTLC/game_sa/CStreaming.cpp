#include "CStreaming.h"
#include "CGame.h"
#include "CTimer.h"
#include "CWanted.h"
#include "CModelInfo.h"
#include "CTheZones.h"
#include <iostream>

CDirectories CStreaming::IMG_FILES[64] = {};
int &CStreaming::ms_currentZoneType = *(int *)0x8E4C20;
unsigned int &CStreaming::ms_streamingBufferSize = *(unsigned int *)0x8E4CA8;
unsigned int &CStreaming::ms_memoryUsed = *(unsigned int *)0x8E4CB4;
unsigned int &CStreaming::ms_numModelsRequested = *(unsigned int *)0x8E4CB8;
bool &CStreaming::ms_disableStreaming = *(bool *)0x9654B0;
CStreamingInfo *CStreaming::ms_aInfoForModel = (CStreamingInfo *)0x8E4CC0;


bool* CStreaming::bCopBikeLoaded = (bool*)0x9654BE;
bool* CStreaming::disablePoliceBikes = (bool*)0x9654BF;
eModelID CStreaming::copModelByTown[5] = { MODEL_CSHER, MODEL_LAPD1, MODEL_SFPD1, MODEL_LVPD1, MODEL_DSHER };
eModelID CStreaming::copCarModelByTown[4] = { MODEL_COPCARRU, MODEL_COPCARLA, MODEL_COPCARSF, MODEL_COPCARVG };
int CStreaming::copModel_curr = 1;
int CStreaming::copCarModel_curr = 1;

void CStreaming::ImGonnaUseStreamingMemory()
{
	((void(__cdecl *)())0x407BE0)();
}

void CStreaming::IHaveUsedStreamingMemory()
{
	((void(__cdecl *)())0x407BF0)();
}

void CStreaming::MakeSpaceFor(unsigned int size)
{
	((void(__cdecl *)(unsigned int))0x40E120)(size);
}

void CStreaming::DisableCopBikes(bool bDisable)
{
	((void(__cdecl *)(bool))0x407D10)(bDisable);
}

unsigned int CStreaming::GetDefaultMedicModel()
{
	return ((unsigned int(__cdecl *)())0x407D20)();
}

unsigned int CStreaming::GetDefaultAmbulanceModel()
{
	return ((unsigned int(__cdecl *)())0x407D30)();
}

unsigned int CStreaming::GetDefaultFiremanModel()
{
	return ((unsigned int(__cdecl *)())0x407D40)();
}

unsigned int CStreaming::GetDefaultFireEngineModel()
{
	return ((unsigned int(__cdecl *)())0x407DC0)();
}

unsigned int CStreaming::GetDefaultCopModel()
{
	//return ((unsigned int(__cdecl *)())0x407C00)();
	unsigned int result; // eax@1
	int v1; // ecx@2

//	result = copModelByTown[CTheZones::m_CurrLevel];
	result = CStreaming::copModelByTown[CStreaming::copModel_curr];
	std::cout << "COP MODEL -> " << result << std::endl;
	if (CStreaming::ms_aInfoForModel[result].m_loadState != 1)
	{
		v1 = 0;
		while (CStreaming::ms_aInfoForModel[CStreaming::copModelByTown[v1]].m_loadState != 1)
		{
			if (++v1 >= (sizeof(copModelByTown) / 4))
				return -1;
		}
		result = CStreaming::copModelByTown[v1];
	}
	return result;
}

unsigned int CStreaming::GetDefaultCopCarModel(unsigned int arg0)
{
	//return ((unsigned int(__cdecl *)())0x407C50)();

	unsigned int result = -1; // eax@4
	signed int count; // edx@7
	int i; // eax@9
	int copCarModel_count = sizeof(copCarModelByTown) / 4;
	copCarModel_curr = rand() % copCarModel_count;

	

	if (!(*bCopBikeLoaded) || arg0 || CStreaming::ms_aInfoForModel[MODEL_COPBIKE].m_loadState != 1)
	{
		result = copCarModelByTown[copCarModel_curr];
		if (CStreaming::ms_aInfoForModel[copModelByTown[copModel_curr]].m_loadState != 1
			|| CStreaming::ms_aInfoForModel[copCarModelByTown[copCarModel_curr]].m_loadState != 1)
		{
			count = copCarModel_count + 1;
			if (arg0)
			count = copCarModel_count;
			i = 0;
			while (CStreaming::ms_aInfoForModel[copModelByTown[i]].m_loadState != 1
				|| CStreaming::ms_aInfoForModel[copCarModelByTown[i]].m_loadState != 1)
			{
				if (++i >= count)
					return -1;
				if (i > copCarModel_count)
					return MODEL_COPBIKE;
			}
			result = copCarModelByTown[i];
		}
//		std::cout << "COP CAR MODEL -> " << result << "test " << *bCopBikeLoaded << std::endl;
	}
	else if (CStreaming::ms_aInfoForModel[MODEL_COPBIKE].m_loadState = 1)
	{
		return MODEL_COPBIKE;
	}
	return result;
}

void CStreaming::LoadAllRequestedModels(bool bOnlyQuickRequests)
{
    ((void(__cdecl *)(bool))0x40EA10)(bOnlyQuickRequests);
}

// Used for loading player clothes
void CStreaming::LoadRequestedModels()
{
    ((void(__cdecl *)())0x40E3A0)();
}

void CStreaming::RemoveAllUnusedModels()
{
    ((void(__cdecl *)())0x40CF80)();
}

void CStreaming::RemoveModel(int modelIndex)
{
    ((void(__cdecl *)(int))0x4089A0)(modelIndex);
}

void CStreaming::RequestModel(int modelIndex, int flags)
{
    ((void(__cdecl *)(int, int))0x4087E0)(modelIndex, flags);
}

void CStreaming::SetModelIsDeletable(int modelIndex)
{
    ((void(__cdecl *)(int))0x409C10)(modelIndex);
}

void CStreaming::SetModelTxdIsDeletable(int modelIndex) 
{
	((void(__cdecl *)(int))0x409C70)(modelIndex);
}


void CStreaming::SetMissionDoesntRequireModel(int modelIndex)
{
    ((void(__cdecl *)(int))0x409C90)(modelIndex);
}

void CStreaming::LoadScene(CVector const& point)
{
    ((void(__cdecl *)(CVector const&))0x40ED80)(point);
}

void CStreaming::LoadSceneCollision(CVector const& coord)
{
    ((void(__cdecl *)(CVector const&))0x40ED80)(coord);
}

void   CStreaming::StreamCopModels(signed int townID)
{
	signed int i; 
	//char* bCopBikeLoaded = (char*)0x9654BE;
	//char* disablePoliceBikes = (char*)0x9654BF;
	signed int* Time_Copbike_refresh = (int*)0x9654C0;
	int copModel_count = sizeof(copModelByTown) / 4;
	int copCarModel_count = sizeof(copCarModelByTown) / 4;
	signed int COP_ID;
	signed int COPCAR_ID; 

	if (!CGame::currArea)
	{
		//ID = townID;
		COP_ID = copModel_curr = rand() % copModel_count;
		COPCAR_ID = copCarModel_curr = rand() % copCarModel_count;

		
		*disablePoliceBikes = 1; //disables policebikes cause I hate them.
		//STREAM BIKER COP(COP&BIKE)
		if (CWanted::FindPlayerWanted(-1) && CWanted::FindPlayerWanted(-1)->m_dwWantedLevel < 3  && !*disablePoliceBikes)
		{
			if (*Time_Copbike_refresh < CTimer::m_snTimeInMilliseconds)
			{
				*bCopBikeLoaded = !(*bCopBikeLoaded);
				*Time_Copbike_refresh = CTimer::m_snTimeInMilliseconds + rand() %  20000 + 30000;
			}

			if (*bCopBikeLoaded)
			{
				if (CStreaming::ms_aInfoForModel[MODEL_COPBIKE].m_loadState == 1 
					&& CStreaming::ms_aInfoForModel[MODEL_LAPDM1].m_loadState == 1)
				{
					CStreaming::SetModelIsDeletable(MODEL_COPBIKE);
					CStreaming::SetModelTxdIsDeletable(MODEL_COPBIKE);
					CStreaming::SetModelIsDeletable(MODEL_LAPDM1);
					CStreaming::SetModelTxdIsDeletable(MODEL_LAPDM1);
				}
				CStreaming::RequestModel(MODEL_COPBIKE, 2);
				CStreaming::RequestModel(MODEL_LAPDM1, 2);
			}
		}
		else
			*bCopBikeLoaded = 0;

		//if (CStreaming::ms_aInfoForModel[ CStreaming::copModelByTown[ID]].m_loadState == 1
		//	&& CStreaming::ms_aInfoForModel[CStreaming::copCarModelByTown[ID]].m_loadState == 1)
		//{
		//	i = 0;
		//	do
		//	{
		//		if (i != ID)
		//		{
		//			CStreaming::SetModelIsDeletable(CStreaming::copModelByTown[i]);
		//		//	CStreaming::SetModelTxdIsDeletable(CStreaming::copModelByTown[i]);
		//			CStreaming::SetModelIsDeletable(CStreaming::copCarModelByTown[i]);
		//			//CStreaming::SetModelTxdIsDeletable(CStreaming::copCarModelByTown[i]);
		//		}
		//		++i;
		//	} while (i < 4);
		//}

		if (CStreaming::ms_aInfoForModel[CStreaming::copCarModelByTown[COPCAR_ID]].m_loadState == 1 
			&& CStreaming::ms_aInfoForModel[CStreaming::copModelByTown[COP_ID]].m_loadState == 1)
		{
			i = 0;
			while (i < copCarModel_count)
			{
				if (i != COPCAR_ID)
				{
					CStreaming::SetModelIsDeletable(CStreaming::copCarModelByTown[i]);
					CStreaming::SetModelTxdIsDeletable(CStreaming::copCarModelByTown[i]);
				}
				i++;
			}
	
			i = 0;
			while (i < copModel_count)
			{
				if (i != COP_ID)
				{
					CStreaming::SetModelIsDeletable(CStreaming::copModelByTown[i]);
					CStreaming::SetModelTxdIsDeletable(CStreaming::copModelByTown[i]);
				}
				i++;
			}
		}

		CStreaming::RequestModel(CStreaming::copModelByTown[COP_ID], 2);
		CStreaming::RequestModel(CStreaming::copCarModelByTown[COPCAR_ID], 2);
	}
}

