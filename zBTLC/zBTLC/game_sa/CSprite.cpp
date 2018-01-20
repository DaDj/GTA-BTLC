#include "CSprite.h"

void CSprite::RenderOneXLUSprite(float x, float y, float z, float halfWidth, float halfHeight, 
								 unsigned char red, unsigned char green, unsigned char blue, 
								 short alpha, float rhw, unsigned char intensity, unsigned char udir, 
								 unsigned char vdir)
{
	((void (__cdecl *)(float, float, float, float, float, unsigned char, unsigned char, unsigned char, 
		short, float, unsigned char, unsigned char, unsigned char))0x70D000)(x, y, z, halfWidth, halfHeight, 
		red, green, blue, alpha, rhw, intensity, udir, vdir);
}

void CSprite::RenderOneXLUSprite_Rotate_Aspect(float x, float y, float z, float unk1, float unk2, int R, int G, int B, int A, float unk3, float unk4, int intensity)
{
	((void(__cdecl *)(float, float, float, float, float, int, int, int, int, float, float, int))0x70D490)(x, y, z, unk1, unk2,
			R, G, B, A, unk3, unk4, intensity);
}

void CSprite::RenderOneXLUSprite2D_Rotate_Dimension(float x, float y, float z, float halfwidth, int halfheight, CRGBA& color, float angle, char intensity)
{
	((void(__cdecl *)(float, float, float, float, int, CRGBA, float, char))0x70F760)(x, y, z, halfwidth, halfheight,
		color, angle, intensity);
}

bool CSprite::CalcScreenCoors(RwV3d const &posn, RwV3d *out, float *w, float *h, bool checkMaxVisible, bool checkMinVisible)
{
	return ((bool (__cdecl *)(RwV3d const &, RwV3d *, float *, float *, bool, bool))0x70CE30)
		(posn, out, w, h, checkMaxVisible, checkMinVisible);
}