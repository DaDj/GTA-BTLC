#pragma once

#include "plbase/PluginBase_SA.h"
#include "RenderWare.h"
#include "List_c.h"
#include "CVector.h"
#include "FxFrustumInfo_c.h"
#include "FxMemoryPool_c.h"

class FxManager_c
{
public:
	List_c m_fxSystemList;
	List_c m_particleList;
	void *m_pFxEmitters;
	List_c m_fxEmitterPrtList;
	int m_nFxTxdIndex;
	CVector *m_pWindDir;
	float *m_pfWindSpeed;
	FxFrustumInfo_c m_frustum;
	int m_nCurrentMatrix;
	RwMatrix *m_apMatrices[8];
	FxMemoryPool_c m_pool;

	void *LoadFxSystemBP(char *filename, int file);
};

VALIDATE_SIZE(FxManager_c, 0xB8);

extern FxManager_c &g_fxMan;