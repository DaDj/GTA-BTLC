#pragma once

#include "plbase/PluginBase_SA.h"

struct ProcObj
{
	char *SurfaceType;
	char *ObjectName;
	float Spacing;
	float Spacingfactor;
	float MinDist;
	float MinRot;
	float MaxRot;
	float MinScale;
	float MaxScale;
	float MinScaleZ;
	float MaxScaleZ;
	float ZOffMin;
	float ZOffMax;
	int align;
	int USERGRID;
};

class CProcObjectMan
{
public:


	char init();
	int LoadDataFile();
};

