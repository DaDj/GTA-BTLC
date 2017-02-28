#pragma once

#include "plbase/PluginBase_SA.h"
#include "RenderWare.h"
#include "CVector.h"

class FxMemoryPool_c
{
public:
	char *data;
	unsigned int size;
	unsigned int position;

	void Optimise();
};

VALIDATE_SIZE(FxMemoryPool_c, 0xC);