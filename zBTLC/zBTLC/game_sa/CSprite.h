#pragma once

#include "plbase/PluginBase_SA.h"
#include "RenderWare.h"
#include "CRGBA.h"

class CSprite
{
public:
	static void RenderOneXLUSprite(float x, float y, float z, float halfWidth, float halfHeight, 
		unsigned char red, unsigned char green, unsigned char blue, short alpha, float rhw, 
		unsigned char intensity, unsigned char udir, unsigned char vdir);


	static void RenderOneXLUSprite_Rotate_Aspect(float x, float y, float z, float unk1,  float unk2, int R, int G, int B, int A, float unk3, float unk4, int intensity);

	static void RenderOneXLUSprite2D_Rotate_Dimension(float x, float y, float z, float halfwidth, int halfheight, CRGBA & color, float angle, char intensity);


	
	static bool CalcScreenCoors(RwV3d const &posn, RwV3d *out, float *w, float *h, bool checkMaxVisible, bool checkMinVisible);
};