#include "CTrafficlights.h"
#include "../Patch/MemoryMgr.h"

CTrafficlights::CTrafficlights()
{
}


void CTrafficlights::Set_polygon_size(int size)
{
	MemoryVP::Patch<char>(0x49DAC6 + 4, size);
}


void CTrafficlights::Set_Trafficlight_models()
{
	CTrafficlights::data entrys[] = {

			{ "bm_nytraflite6c", 0x5B58F7 + 1 },
			{ "BM_NYtrafflite_11", 0x5B5915 + 1 },
			{ "BM_NYtraflite6d", 0x5B5936 + 1 },
			{ "BM_NYtraflite6d2", 0x5B5906 + 1 },
			{ "BM_NYtraflite6c2", 0x5B60A7 + 1 },
			{ "BM_NYtraflite10", 0x5B60B6 + 1 },
			{ "BM_NYtraflite3a", 0x5B60C5 + 1 },
			{ "BM_NYtraflite2b", 0x5B60D4 + 1 },
			{ "BM_NYtraflite8", 0x5B5924 + 1 },
	};
	int num = sizeof(entrys) / sizeof(entrys[0]);

	for ( int i = 0; i < num ; i++)
	{
		MemoryVP::Patch<void*>(entrys[i].adress, entrys[i].name); //Trafficlight replacement
	}
	
}

void CTrafficlights::Set_Trafficlight_PED_COORD()
{
	MemoryVP::Patch<float>(0x49E107, -0.101f); //ztop
	MemoryVP::Patch<float>(0x49E111, 0.509f); //ytop
	MemoryVP::Patch<float>(0x49E11B, 2.38f); //xtop
	MemoryVP::Patch<float>(0x49E131, -0.101f); //zbottom
	MemoryVP::Patch<float>(0x49E13B, 0.111f); //ybottom
	MemoryVP::Patch<float>(0x49E145, 2.753f); //xbottom

}