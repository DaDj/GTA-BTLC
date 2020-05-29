/*
    Plugin-SDK (Grand Theft Auto) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "plbase/PluginBase_SA.h"
#include "ListItem_c.h"
#include "FxSphere_c.h"


enum eFxInfo
{
	FX_INFO_EMRATE_DATA = 0x1001,
	FX_INFO_EMSIZE_DATA = 0x1004,
	FX_INFO_EMSPEED_DATA = 0x1008,
	FX_INFO_EMDIR_DATA = 0x1010,
	FX_INFO_EMANGLE_DATA = 0x1020,
	FX_INFO_EMLIFE_DATA = 0x1040,
	FX_INFO_EMPOS_DATA = 0x1080,
	FX_INFO_EMWEATHER_DATA = 0x1100,
	FX_INFO_EMROTATION_DATA = 0x1200,
	FX_INFO_NOISE_DATA = 0x2001,
	FX_INFO_FORCE_DATA = 0x2002,
	FX_INFO_FRICTION_DATA = 0x2004,
	FX_INFO_ATTRACTPT_DATA = 0x2008,
	FX_INFO_ATTRACTLINE_DATA = 0x2010,
	FX_INFO_GROUNDCOLLIDE_DATA = 0x2020,
	FX_INFO_WIND_DATA = 0x2040,
	FX_INFO_JITTER_DATA = 0x2080,
	FX_INFO_ROTSPEED_DATA = 0x2100,
	FX_INFO_FLOAT_DATA = 0x2200,
	FX_INFO_UNDERWATER_DATA = 0x2400,
	FX_INFO_COLOUR_DATA = 0x4001,
	FX_INFO_SIZE_DATA = 0x4002,
	FX_INFO_SPRITERECT_DATA = 0x4004,
	FX_INFO_HEATHAZE_DATA = 0x4008,
	FX_INFO_TRAIL_DATA = 0x4010,
	FX_INFO_FLAT_DATA = 0x4020,
	FX_INFO_DIR_DATA = 0x4040,
	FX_INFO_ANIMTEX_DATA = 0x4080,
	FX_INFO_COLOURRANGE_DATA = 0x4100,
	FX_INFO_SELFLIT_DATA = 0x4200,
	FX_INFO_COLOURBRIGHT_DATA = 0x4400,
	FX_INFO_SMOKE_DATA = 0x8001,
};


class FxSystem_c;

/* FX System BluePrint */

class FxSystemBP_c : public ListItem_c {
public:
    unsigned int m_nNameKey;
    float m_fLength;
    float m_fLoopIntervalMin;
    float m_fLoopLength;
    short m_nCullDist;
    unsigned char m_nPlayMode;
    unsigned char m_nNumEmitters;
    void **m_emittersList;
    FxSphere_c *m_pBoundingSphere;

    FxSystemBP_c();
    ~FxSystemBP_c();
    static void* operator new(unsigned int size);
    void Unload();
    unsigned int Update(float arg0);
    void Render(RwCamera* camera, float arg1, unsigned char arg2);
    bool FreePrtFromSystem(FxSystem_c* system);
    FxSphere_c* GetBoundingSphere();
    void SetBoundingSphere(RwV3d* center, float radius);
    void Load(char* filename, int file, int version);
};

VALIDATE_SIZE(FxSystemBP_c, 0x24);