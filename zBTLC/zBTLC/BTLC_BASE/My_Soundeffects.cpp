#include "My_Soundeffects.h"
#include "../game_sa/CWeather.h"
#include "../game_sa/CZone.h"
#include "../game_sa/CTheZones.h"
#include "../game_sa/CHud.h"

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
	if (  CHud::m_ZoneName && !_stricmp(CHud::m_ZoneName, "Easton"))
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




 void CMySoundeffects::Init()
 {
	 MemoryVP::InjectHook(0x4D7B50, &SetChannelAdditionalFX, PATCH_JUMP);
	 MemoryVP::Nop(0x4D9899, 5);
 }



CMySoundeffects::CMySoundeffects()
{
}
