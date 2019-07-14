#pragma once
#include "plbase/PluginBase_SA.h"
#include "CClumpModelInfo.h"
#include "RenderWare.h"

class CCarFxRender
{
public:
	//Dirttextures
	static RwTexture **ms_aDirtTextures; //vehiclegrunge256 (vanilla SA)
	static RwTexture *ms_aDirtTextures_2[16];//vehicle_genericmud_truck from IV
	static RwTexture *ms_aDirtTextures_3[16];//unused
	static RwTexture *ms_aDirtTextures_4[16];//unused
	static RwTexture *ms_aDirtTextures_5[16];//unused
	static RwTexture *ms_aDirtTextures_6[16];//unused

	static void Shutdown();
	static void InitialiseDirtTexture();
	static void MyShutdown();
	static void MyInitialiseDirtTextures();
	static void MyInitialiseDirtTextureSingle(char* name, RwTexture** Array);
	static void MyInit();
};