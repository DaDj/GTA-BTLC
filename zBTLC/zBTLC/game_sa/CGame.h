#pragma once

#include "plbase/PluginBase_SA.h"

class CGame
{
public:
	// Current number of area
	static int& currArea;

	static void TidyUpMemory(bool arg1, bool arg2);
};