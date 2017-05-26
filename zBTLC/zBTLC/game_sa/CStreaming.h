#pragma once

#include "plbase/PluginBase_SA.h"
#include "CVector.h"
#include "RenderWare.h"
#include "CStreamingInfo.h"
#include "eModelID.h"

 struct CDirectories
{
	char name[40];
	char isNotPlayerImg;//40 //0x28
	char gap_29[3]; //41
	int streamHandle = 0; //44 0x2c
};


class  CStreaming
{
public:
    static int &ms_currentZoneType;
    static unsigned int &ms_streamingBufferSize;
    static unsigned int &ms_memoryUsed;
    static unsigned int &ms_numModelsRequested;
    static bool &ms_disableStreaming;
	static CStreamingInfo *ms_aInfoForModel;
	static void My_Init();
	static void ImGonnaUseStreamingMemory();
	static void IHaveUsedStreamingMemory();
	static void MakeSpaceFor(unsigned int size);



    static void DisableCopBikes(bool bDisable);
    static unsigned int GetDefaultMedicModel();
    static unsigned int GetDefaultAmbulanceModel();
    static unsigned int GetDefaultFiremanModel();
    static unsigned int GetDefaultFireEngineModel();
    static unsigned int GetDefaultCopModel();
    static unsigned int GetDefaultCopCarModel(unsigned int arg0);
    static void LoadAllRequestedModels(bool bOnlyQuickRequests);
    // Used for player clothes
    static void LoadRequestedModels();

    static void RemoveAllUnusedModels();
    static void RemoveModel(int modelIndex);
    static void RequestModel(int modelIndex, int flags);
    static void SetModelIsDeletable(int modelIndex);
	static void SetModelTxdIsDeletable(int modelIndex);
    static void SetMissionDoesntRequireModel(int modelIndex);
    static void LoadScene(CVector const& point);
    static void LoadSceneCollision(CVector const& coord);

	static CDirectories IMG_FILES[64];

	static eModelID copModelByTown[5];
	static eModelID copCarModelByTown[4];
	static int copModel_curr;
	static int copCarModel_curr;
	static bool* bCopBikeLoaded;
	static bool* disablePoliceBikes;
	static void StreamCopModels(signed int townID);

};