#pragma once
#include "../game_sa/CStreaming.h"
namespace limits
{
	//more IMG's loadable.
	void IMG_LIMIT(); 
	void Init();
	void vehicleColourTable();
	int AddImageToList(LPCSTR lpFileName, char notPlayerFile);
	namespace Water_limit
	{
		void init();
	}
}