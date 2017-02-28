#pragma once
#include "../game_sa/CStreaming.h"
namespace limits
{
	//more IMG's loadable.
	void IMG_LIMIT(); 
	int AddImageToList(LPCSTR lpFileName, char notPlayerFile);
}