#include "CWaterlevel.h"
#include "Cvector.h"

  CWaterVertex CWaterlevel::Vertices[2021] = {};
  CWaterQuad CWaterlevel::Quads[601] = {};
  CWaterTriangle CWaterlevel::Triangles[12] = {};
 short CWaterlevel::QuadsandTrianglesList[801];

 bool CWaterlevel::GetWaterLevelNoWaves(CVector pos, float * pOutWaterLevel, float * pOutBigWaves, float * pOutSmallWaves) {
	 return plugin::CallAndReturn<bool, 0x6E8580, CVector, float *, float *, float *>(pos, pOutWaterLevel, pOutBigWaves, pOutSmallWaves);
 }

