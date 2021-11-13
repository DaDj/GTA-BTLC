//////////////////////////////////////////////////////////////////
////              FAST LOADER - INSTANT GAME START            ////
//////////////////////////////////////////////////////////////////
//// Author: D4DJ/TAG     VERSION: 1.0    DATE: 18.08.2016    ////
//////////////////////////////////////////////////////////////////
//// Description:                                             ////
//// fast game launching.                                     ////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include "../Patch/MemoryMgr.h"


namespace fastload 
{
#define SKIP_LOADSCREEN  1
	static int prevDisplayedSplash = 1;
	static float Loadscreen_Time = 1.01f;
	
	//Fix for the non-looping splashes
	void IncreaseDisplayedSplash()
	{
		int* currDisplayedSplash = (int*)0x8D093C;
		prevDisplayedSplash = 1 + *currDisplayedSplash;  // (+1 because the offset the game uses to access the texture array)
		if (++*currDisplayedSplash >= 7)
			*currDisplayedSplash = 1;
	}

	// Simulate that the copyright screen happened
	void SimulateCopyrightScreen()
	{
		int* currDisplayedSplash = (int*)0x8D093C;
		float* timesincelastscreen = (float*)0xBAB340;
		char* firstloadscreensplash = (char*)0xBAB31E;
		*currDisplayedSplash = 0;       // Previous splash index = copyright notice
		*timesincelastscreen -= 1000.0;// Decrease timeSinceLastScreen, so it will change immediately
		*firstloadscreensplash = 1;      // First Loading Splash
	}

	void Init()
	{
	MemoryVP::Nop(0x747483, 6);         // Disable gGameState = 0 setting
	MemoryVP::Patch<int>(0xC8D4C0, 5);  // Put the game where the user wants (default's to the copyright screen)
	MemoryVP::InjectHook(0x590AE4, 0x590C9E, PATCH_JUMP);  // Skip fading screen rendering

		MemoryVP::Nop(0x590ADE + 5, 1);
		MemoryVP::InjectHook(0x590ADE, &IncreaseDisplayedSplash, PATCH_CALL);

		//disablecopyright screen
		MemoryVP::Nop(0x748C2B, 5);
		MemoryVP::InjectHook(0x748C9A, &SimulateCopyrightScreen);

		//loadscreentime
		MemoryVP::Patch<void*>(0x590DA4 + 2, &Loadscreen_Time);

		if (SKIP_LOADSCREEN)
		{
			// Disable loading bar rendering
			MemoryVP::Nop(0x5905B4, 5);
			// Disable audio tune from loading screen
			MemoryVP::Nop(0x748CF6, 5);  
			// Disable loading screen rendering
			MemoryVP::Nop(0x590D9F, 5);
			MemoryVP::Patch<char>(0x590D9F, 0xC3);
		}
	}

}