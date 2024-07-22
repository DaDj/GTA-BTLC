#include "My_Soundeffects.h"
#include "../game_sa/CWeather.h"
#include "../game_sa/CZone.h"
#include "../game_sa/CTheZones.h"
#include "../game_sa/CHud.h"
#include "../game_sa/CCamera.h"
#include "../game_sa/CVector.h"

char *envNames[] = {
	"GENERIC",
	"PADDEDCELL",
	"ROOM",
	"BATHROOM",
	"LIVINGROOM",
	"STONEROOM",
	"AUDITORIUM",
	"CONCERTHALL",
	"CAVE",
	"ARENA",
	"HANGAR",
	"CARPETEDHALLWAY",
	"HALLWAY",
	"STONECORRIDOR",
	"ALLEY",
	"FOREST",
	"CITY",
	"MOUNTAINS",
	"QUARRY",
	"PLAIN",
	"PARKINGLOT",
	"SEWERPIPE",
	"UNDERWATER",
	"DRUGGED",
	"DIZZY",
	"PSYCHOTIC"
};

constexpr float invLerp(float fMin, float fMax, float fVal) {
	return (fVal - fMin) / (fMax - fMin);
}


int CMySoundeffects::gCurrentEnvironment = 0;

int CMySoundeffects::SetReverbEnv()
{
	//When under water
	if (CWeather::UnderWaterness > 0)
		return EAX_ENVIRONMENT_UNDERWATER;

	//When in Tunnelcullzone
	if (CWeather::InTunnelness > 0)
		return EAX_ENVIRONMENT_HANGAR;

	//Zone Comparer
	if (CHud::m_ZoneName && !_stricmp(CHud::m_ZoneName, "The Exchange"))
		return EAX_ENVIRONMENT_CONCERTHALL;
	
	
	return EAX_ENVIRONMENT_CITY;
}

//Also check out that fucntion for audio zones. Pretty nice. basically already implemented
//char __thiscall CAEAudioHardware::UpdateReverbEnvironment(CAEAudioHardware *this)

 void __fastcall CMySoundeffects::SetChannelAdditionalFX(CAEStaticChannel *channel, int, bool compressed) {
	if (channel->m_pDirectSoundBuffer && channel->m_pDirectSound3DBuffer) {
		if (*(unsigned char *)0xB60660 == 1) {
			IKsPropertySet *propertySet = NULL;
			if (SUCCEEDED(channel->m_pDirectSound3DBuffer->QueryInterface(IID_IKsPropertySet, reinterpret_cast<LPVOID*>(&propertySet)))) {
				unsigned int roomLevel = -10000;
				if (compressed)
					roomLevel = 0;
				propertySet->Set(EAXPROPERTYID_EAX40_Source, EAXSOURCE_ROOM, 0, 0, &roomLevel, 4);
				if (FindPlayerPed())
					gCurrentEnvironment = SetReverbEnv();
			
				propertySet->Set(EAXPROPERTYID_EAX40_FXSlot0, EAXREVERB_ENVIRONMENT, 0, 0, &gCurrentEnvironment, 4);
			//	propertySet->Set(EAXPROPERTYID_EAX40_FXSlot0, EAXREVWER)
				propertySet->Release();
			}
		}
	}
}


 float CMySoundeffects::GetDirectionalMikeAttenuation(const CVector& soundDir) {
	 // https://en.wikipedia.org/wiki/Cutoff_frequency
	 static constexpr float fCutoffFrequency = 0.70710678118F; // sqrt(0.5F);
	 static constexpr float fAttenuationMult = -6.0F;

	 CVector vecDir = soundDir;
	 vecDir.Normalise();

	 // BUG? Seems weird that it uses just single axis, seems like it should be normalized Dot product with for example Camera direction, to work the same way regardless of
	 // direction
	 const auto  freq = vecDir.y; //freq = (vecDir.x + vecDir.z) * 0.0F + vecDir.y; 
	 if (fCutoffFrequency == -1.0F || freq >= fCutoffFrequency)
		 return 0.0F;

	 if (freq <= -fCutoffFrequency)
		 return fAttenuationMult;

	 return (1.0F - invLerp(-fCutoffFrequency, fCutoffFrequency, freq)) * fAttenuationMult;
 }

 void CMySoundeffects::GetPositionRelativeToCamera(CVector* vecOut, const CVector* vecPos) {
	 static const float fFirstPersonMult = 2.0F;
	 if (!vecPos)
		 return;

	 const auto camMode = TheCamera.m_aCams[TheCamera.m_nActiveCam].m_eMode;
	 if (camMode == eCamMode::MODE_SNIPER || camMode == eCamMode::MODE_ROCKETLAUNCHER || camMode == eCamMode::MODE_1STPERSON) {
		 const auto& tempMat = TheCamera.m_mCameraMatrix;
		 const auto& vecCamPos = TheCamera.GetPosition();
		 const auto  vecOffset = *vecPos - (vecCamPos - tempMat.GetForward() * fFirstPersonMult);

		 vecOut->x = -DotProduct(vecOffset, tempMat.GetRight());
		 vecOut->y = DotProduct(vecOffset, tempMat.GetForward());
		 vecOut->z = DotProduct(vecOffset, tempMat.GetUp());
		 return;
	 }

	 auto  fMult = 0.0F;
	 auto* player = FindPlayerPed();
	 if (player)
	 {
		 fMult = min(0.5f, DistanceBetweenPoints(TheCamera.GetPosition(), player->GetPosition()));
		 fMult = max(0.0f, fMult);
	 }
		

		 
	 const auto& tempMat = TheCamera.m_mCameraMatrix;
	 const auto& vecCamPos = TheCamera.GetPosition();
	 const auto  vecOffset = *vecPos - (vecCamPos + tempMat.GetForward() * fMult);

	 vecOut->x = -DotProduct(vecOffset, tempMat.GetRight());
	 vecOut->y = DotProduct(vecOffset, tempMat.GetForward());
	 vecOut->z = DotProduct(vecOffset, tempMat.GetUp());
 }




 void CMySoundeffects::Init()
 {
	 MemoryVP::InjectHook(0x4D7B50, &SetChannelAdditionalFX, PATCH_JUMP);
	 MemoryVP::InjectHook(0x4D7F60, &GetDirectionalMikeAttenuation, PATCH_JUMP);
	 MemoryVP::InjectHook(0x4D80B0, &GetPositionRelativeToCamera, PATCH_JUMP);
	 MemoryVP::Nop(0x4D9899, 5);
 }



CMySoundeffects::CMySoundeffects()
{
}
