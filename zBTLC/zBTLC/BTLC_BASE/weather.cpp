//////////////////////////////////////////////////////////////////
////              BTLC    WEATHER       					  ////
//////////////////////////////////////////////////////////////////
//// Author: D4DJ         VERSION: 2.0    DATE: 02.08.2016    ////
//////////////////////////////////////////////////////////////////
//// Description:                                             ////
//// weather changes and rain changes                         ////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include "../Patch/MemoryMgr.h"
#include "../game_sa/CStreaming.h"


namespace weather
{
	
	///<summary>
	///more intense rain.
	///</summary>
	void enhanced_rain()
	{
		for (int a = 0; a < 60; a++)
		{
			((void(_cdecl*)())0x72AF70)();
		}

	}



	///<summary>
	///different shadow opacity depending on time and weather.
	///</summary>
	void weather_effects()
	{
		//some GTA weather variables -> should be reloacted to a weather class.
		int CWeather_LightningFlash = *(int*)0xC812CC;
		float CWeather_Rain = *(float*)0xC81324;
		int CWeather_bRain = *(int*)0xC81328;
		int CClock_hours = (*(byte*)0xB70153);
		int CShadow_dynamic = 1;

		//run enhanced rain
		enhanced_rain();

		//if (CWeather_Rain > 0.1)
		//{
		//	if (CWeather_LightningFlash)
		//	{
		//		MemoryVP::Patch<char>(0x71162C, 255); //stencilopacity
		//		//CShadow_dynamic = 1;
		//	}
		//	else
		//	{
		//		MemoryVP::Patch<char>(0x71162C, 5); //stencilopacity
		//		//CShadow_dynamic = 0;
		//	}
		//}
		//else
		//	MemoryVP::Patch<char>(0x71162C, 90); //stencilopacity
		//if (!CWeather_LightningFlash && (CClock_hours > 20 || CClock_hours < 7))
		//{
		//	if (CClock_hours > 21 || CClock_hours <= 3)
		//	{
		//		MemoryVP::Patch<char>(0x71162C, 2); //stencilopacity
		//		CShadow_dynamic = 0;
		//	}
		//	if (CShadow_dynamic == 1)
		//	{
		//		if (CClock_hours < 22 && CClock_hours > 7)
		//		{
		//			if (CClock_hours == 19)
		//				MemoryVP::Patch<char>(0x71162C, 50); //stencilopacity
		//			else if (CClock_hours == 20)
		//				MemoryVP::Patch<char>(0x71162C, 40); //stencilopacity
		//			else if (CClock_hours == 21)
		//				MemoryVP::Patch<char>(0x71162C, 10); //stencilopacity
		//		}
		//		if (CClock_hours < 7)
		//		{
		//			if (CClock_hours == 4)
		//				MemoryVP::Patch<char>(0x71162C, 10); //stencilopacity
		//			else if (CClock_hours == 5)
		//				MemoryVP::Patch<char>(0x71162C, 40); //stencilopacity
		//			else if (CClock_hours == 6)
		//				MemoryVP::Patch<char>(0x71162C, 60); //stencilopacity
		//		}
		//	}
		//}
	}

	///<summary>
	///init for better rain effects
	///</summary>
	void enhanced_rain_init()
	{
		static float
			rainstreak_pos = 3.0f,//
			rainstreak_size = 3.0,//
			rainstreak_posx_rand = 1.5f,
			rainstreak_posy_rand = 2.0f,
			rainstreak_alpha = 0.3f,
			rainsplash_val2 = 4.1f,//
			rainsplash_val1 = 8.1f, //
			rainsplash_loop = 10.0f,
			raincloud_pos2 = 0.0f,
			raincloud_pos1 = 3.0f;

		//rainstreak adjustments
		MemoryVP::Patch<float*>(0x72B21E + 2, &rainstreak_pos); //posy 
		MemoryVP::Patch<float*>(0x72B1CF + 2, &rainstreak_pos); //posx 
		MemoryVP::Patch<float*>(0x72B276 + 2, &rainstreak_pos); //posz 
		MemoryVP::Patch<float*>(0x72B1C5 + 2, &rainstreak_size);//size x
		MemoryVP::Patch<float*>(0x72B213 + 2, &rainstreak_size);//size y
		MemoryVP::Patch<float*>(0x72B26B + 2, &rainstreak_size);//size z
		MemoryVP::Patch<float*>(0x72B289 + 2, &rainstreak_alpha);//alpha
		MemoryVP::Patch<float*>(0x72B3CA + 2, &rainstreak_posy_rand);//random posy
		MemoryVP::Patch<float*>(0x72B3A7 + 2, &rainstreak_posx_rand);//random posx

		//rain splashes stuff(textures on the ground)
		MemoryVP::Patch<float*>(0x72AD12 + 2, &rainsplash_val1);
		MemoryVP::Patch<float*>(0x72ACEB + 2, &rainsplash_val1);
		MemoryVP::Patch<float*>(0x72AD1C + 2, &rainsplash_val2);
		MemoryVP::Patch<float*>(0x72ACF5 + 2, &rainsplash_val2);
		MemoryVP::Patch<float*>(0x72AB16 + 2, &rainsplash_loop);
		MemoryVP::Patch<float>(0x72AB87 + 1, 0.04f); //splashsize

		//rain clouds/smoke(on the ground)
		MemoryVP::Patch<float>(0x72ADF7 + 1, 0.4f); //raincloud_size
		MemoryVP::Patch<float>(0x72ADDD + 1, 0.5f); //raincloud_alpha
		MemoryVP::Patch<float*>(0x72AEF0 + 2, &raincloud_pos1);
		MemoryVP::Patch<float*>(0x72AEE6 + 2, &raincloud_pos2);

		//rain car wheel spray
		//reduces wheel spray -> nice visuals
		MemoryVP::Patch<float>(0x49FEB4 + 1, 0.7f);
		//MemoryVP::Patch<float>(0x49FEC0 + 1, -0.4);
		//MemoryVP::Patch<float>(0x49FC2D + 1, 0.1);
		MemoryVP::Patch<float>(0x49FC55 + 4, 0.2f);
		MemoryVP::Patch<float>(0x49FC8F + 4, 0.2f);
	}

	///<summary>
	///weather related adjustments
	///</summary>
	void init()
	{
		//init enhanced rain adjustments
		enhanced_rain_init();
		
		//Set weather zone permamently to 2
		MemoryVP::Patch<char>(0x72A6A8 + 7, 2);
		MemoryVP::Patch<char>(0x72A6E8 + 7, 2);
		MemoryVP::Patch<char>(0x72A76C + 7, 2);
		MemoryVP::Patch<char>(0x72A782 + 7, 2);

		//Disable RAIN NOISE
		MemoryVP::Nop(0x705078, 5);
		//MakeNOP(0x72C7C0, 5);
		//MakeNOP(0x72AAE0, 5);
		//MakeNOP(0x53E126, 5);

		//hook weather effects
		MemoryVP::InjectHook(0x53E126, &weather_effects);

	}
	
}