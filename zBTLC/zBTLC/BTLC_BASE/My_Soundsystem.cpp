#include <initguid.h>

#include "../game_sa/common.h"
#include "../BTLC_BASE/other_shared.h"
#include "../game_sa/CGame.h"
#include "../game_sa/eax4.h"
#include "../game_sa/CAEStaticChannel.h"

namespace My_Soundsystem
{
	int gCurrentEnvironment = 0;
	//int Check_AudioArea(int &a1, int &a2)
	//{
	//	int result = 0; // eax@2
	//	__int16 v3 = -1; // ax@4
	//	int v4; // eax@10
	//	int CWeather_UnderWaterness = *(int*)0xC8132C;
	//	int dword_B6DCC0 = *(int*)0xB6DCC0;
	//	int dword_B6DCBC = *(int*)0xB6DCBC;
	//	int dword_B6DC94 = *(int*)0xB6DC94;
	//	int dword_B6DC6C = *(int*)0xB6DC6C;
	//	__int16 **word_B6EBB0 = (__int16**)0xB6EBB0;
	//	__int16 **word_B6DCD8 = (__int16**)0xB6DCD8;
	//	bool **byte_8AD670 = (bool**)0x8AD670;
	//	bool **byte_8AD674 = (bool**)0x8AD674;
	//	if (CWeather_UnderWaterness >= 0.5)
	//	{
	//		result = a1;
	//		a1 = 0;
	//		a2 = -100;
	//		return result;
	//	}
	//	//	if (!dword_B6DCC0 <= 0)
	//	//v3 = *word_B6EBB0[14 * dword_B6DC94];
	//	//else
	//	//{
	//	//if (dword_B6DCBC <= 0)
	//	//{
	//	//result = CGame::currArea;
	//	//if (CGame::currArea)
	//	//v3 = 14;
	//	//}
	//	//else
	//	//v3 = *word_B6DCD8[12 * dword_B6DC6C];
	//	//}
	//	//result = CGame::currArea;
	//	//if (CGame::currArea)
	//	//v3 = 14;
	//	//if (v3 != -1)
	//	//{
	//	//v4 = 8 * v3;
	//	//a1 = (int)byte_8AD670[v4];
	//	//result = (int)byte_8AD674[v4];
	//	//a2 = result;
	//	//return result;
	//	//}
	//
	//	a1 = 800;
	//	a2 = 800;
	//	result = a1;
	//	return result;
	//}
	static void __fastcall SetChannelAdditionalFX(CAEStaticChannel *channel, int, bool compressed) 
	{
		if (channel->m_pDirectSoundBuffer && channel->m_pDirectSound3DBuffer) {
			if (*(unsigned char *)0xB60660 == 1) {
				IKsPropertySet *propertySet = NULL;
				if (SUCCEEDED(channel->m_pDirectSound3DBuffer->QueryInterface(IID_IKsPropertySet, reinterpret_cast<LPVOID*>(&propertySet)))) {
					unsigned int roomLevel = -10000;
					if (compressed)
						roomLevel = 0;
					propertySet->Set(EAXPROPERTYID_EAX40_Source, EAXSOURCE_ROOM, 0, 0, &roomLevel, 4);
					gCurrentEnvironment = EAX_ENVIRONMENT_CITY;
					if(true)
						gCurrentEnvironment = EAX_ENVIRONMENT_HANGAR;
					propertySet->Set(EAXPROPERTYID_EAX40_FXSlot0, EAXREVERB_ENVIRONMENT, 0, 0, &gCurrentEnvironment, 4);
					propertySet->Release();
				}
			}
		}
	}


	void init()
	{
		//MemoryVP::InjectHook(0x4D8010, &My_Soundsystem::Check_AudioArea, PATCH_JUMP);
		MemoryVP::InjectHook(0x4D7B50, &SetChannelAdditionalFX, PATCH_JUMP);
		MemoryVP::Nop(0x4D9899, 5);
	}


}