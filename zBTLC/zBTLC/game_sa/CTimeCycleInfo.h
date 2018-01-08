#pragma once

#include "plbase/PluginBase_SA.h"

#pragma pack(push, 4)
class  CTimeCycleInfo 
{
public:
	float            m_fCurrentAmbientRed;
	float            m_fCurrentAmbientGreen;
	float            m_fCurrentAmbientBlue;
	float            m_fCurrentAmbientObjRed;
	float            m_fCurrentAmbientObjGreen;
	float            m_fCurrentAmbientObjBlue;
	unsigned int m_fCurrentDirectionalRed;
	unsigned int m_fCurrentDirectionalGreen;
	unsigned int m_fCurrentDirectionalBlue;
	unsigned short m_nCurrentSkyTopRed;
	unsigned short m_nCurrentSkyTopGreen;
	unsigned short m_nCurrentSkyTopBlue;
	unsigned short m_nCurrentSkyBottomRed;
	unsigned short m_nCurrentSkyBottomGreen;
	unsigned short m_nCurrentSkyBottomBlue;
	unsigned short m_nCurrentSunCoreRed;
	unsigned short m_nCurrentSunCoreGreen;
	unsigned short m_nCurrentSunCoreBlue;
	unsigned short m_nCurrentSunCoronaRed;
	unsigned short m_nCurrentSunCoronaGreen;
	unsigned short m_nCurrentSunCoronaBlue;
	float            m_fCurrentSunSize;
	float            m_fCurrentSpriteSize;
	float            m_fCurrentSpriteBrightness;
	unsigned short m_nCurrentShadowStrength;
	unsigned short m_nCurrentLightShadowStrength;
	unsigned short m_nCurrentPoleShadowStrength;
	float            m_fCurrentFarClip;
	float            m_fCurrentFogStart;
	float            m_fCurrentLightsOnGroundBrightness;
	unsigned short m_nCurrentLowCloudsRed;
	unsigned short m_nCurrentLowCloudsGreen;
	unsigned short m_nCurrentLowCloudsBlue;
	unsigned short m_nCurrentFluffyCloudsBottomRed;
	unsigned short m_nCurrentFluffyCloudsBottomGreen;
	unsigned short m_nCurrentFluffyCloudsBottomBlue;
	float            m_fCurrentWaterRed;
	float            m_fCurrentWaterGreen;
	float            m_fCurrentWaterBlue;
	float            m_fCurrentWaterAlpha;
	float            m_fRGB1_R;
	float            m_fRGB1_G;
	float            m_fRGB1_B;
	float            m_fAlpha1;
	float            m_fRGB2_R;
	float            m_fRGB2_G;
	float            m_fRGB2_B;
	float            m_fAlpha2;
	float            m_fCloudAlpha1;
	unsigned int m_dwCloudAlpha2;
	unsigned short m_wCloudAlpha3;
	float            m_fIllumination;
	float field_A8;
};
#pragma pack(pop)

VALIDATE_SIZE(CTimeCycleInfo, 0xAC);

extern  CTimeCycleInfo *TimeCycleInfo;