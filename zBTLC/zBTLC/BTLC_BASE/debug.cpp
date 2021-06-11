
#include "debug.h"
#include <Windows.h>
#include "../Patch/MemoryMgr.h"
#include <sstream>
#include <iostream>
#include "../Events_SA/Events_SA.h"
#include "../game_sa/RenderWare.h"
#include "../game_sa/CFileLoader.h"
#include "../game_sa/CWorld.h"
#include "../game_sa/common.h"
#include "../game_sa/CHud.h"
#include "../game_sa/CTimer.h"
#include "../game_sa/CSprite.h"
#include "../game_sa/CFont.h"
#include "../game_sa/CMenuManager.h"
#include "../game_sa/CVehicleModelInfo.h"
#include "../game_sa/CTxdStore.h"
#include "../game_sa/CClothesBuilder.h"
#include "../game_sa/CCamera.h"
#include "../game_sa/FxManager_c.h"
#include "../game_sa/CAEStaticChannel.h"
#pragma once
DebugMenuAPI gDebugMenuAPI;
void(*DebugMenuProcess)(void);
void(*DebugMenuRender)(void);
static void stub(void) { };



namespace debug
{
	
	void init()
	{
	

		debug_console();
		MemoryVP::InjectHook(0x405E0A, &CFileLoader::LoadObjectInstance_a, PATCH_CALL);
		MemoryVP::InjectHook(0x4062F2, &CFileLoader::LoadObjectInstance_a, PATCH_CALL);
		MemoryVP::InjectHook(0x5B892A, &CFileLoader::LoadObjectInstance_a, PATCH_CALL);

		//plugin::Events::drawMenuBackgroundEvent += []
		//{
		//	
		//	char string[40];
		//	CFont::SetColor(CRGBA::CRGBA(200, 200, 200, 255));
		//	sprintf(string, "FPS : %f", FrontEndMenuManager.m_fDrawDistance);
		//	CFont::SetFontStyle(FONT_SUBTITLES);
		//	CFont::SetAlignment(ALIGN_LEFT);
		//	CFont::SetOutlinePosition(1);
		//	CFont::SetScale(CHud::x_fac(0.25f), CHud::y_fac(0.5f));
		//	CFont::PrintString(CHud::x_fac(200.0f), CHud::y_fac(5.0f), string);



		//	static float test_lod = 5.0;
		//	static float test_lod2 = 1/(test_lod - 0.925);
		//	
		//	MemoryVP::Patch<void*>(0x573592 + 2, &test_lod);
		//	MemoryVP::Patch<float>(0x57359F + 3, test_lod);
		//	MemoryVP::Patch<float>(0x865438, test_lod2);
		//	MemoryVP::Patch<float>(0x865250, (test_lod - 0.925) / 16);
		//	//float thing1 = *(float*)0x57AED6 + 2;
		//	//float thing = *(float*)0x865438;

		//};

		plugin::Events::gameProcessEvent += []
		{
			//MemoryVP::Patch<int>(0xC7C70D, 1); //Liftcam
			//MemoryVP::Patch<int>(0xC7C70C, 1);	//videocam
		
		};

		plugin::Events::drawHudEvent += []
		{
			draw_current_Modelname();
			draw_FPS();
			//draw_graphics_info();


		/*	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void *>(rwFILTERLINEAR));
			if (CVehicleModelInfo::ms_pCustomLightsTexture)
			{
				RwRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
				RwRenderStateSet(rwRENDERSTATETEXTURERASTER, CVehicleModelInfo::ms_pCustomLightsTexture->raster);
				CSprite::RenderOneXLUSprite(180,180,1,100,100,255,255,255,255,1,255,0,0 );
				RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
			}


			RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void *>(rwFILTERLINEAR));
			if (CVehicleModelInfo::ms_pCustomLightsTexture)
			{
				RwRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
				RwRenderStateSet(rwRENDERSTATETEXTURERASTER, CVehicleModelInfo::ms_pCustomLightsOnTexture->raster);
				CSprite::RenderOneXLUSprite(280, 280, 1, 100, 100, 255, 255, 255, 255, 1, 255, 0, 0);
				RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
			}*/


			//CPed *player = FindPlayerPed(-1);
			//	if (player && player->m_pVehicle && player->m_bInVehicle )
			//	{
			//		
			//		float speed = player->m_pVehicle->m_fGasPedal;
			//		std::cout<< speed << '\r';
			//	}
		};
	}

	void debug_console()
	{
		MemoryVP::InjectHook(0x821982, printf, PATCH_JUMP);
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdout);
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stderr);
		int process = GetCurrentProcessId();
		// Screens
		// If you have multiple screens, this will automatically move the co0nsole to the 2nd
		if (GetSystemMetrics(SM_CMONITORS) > 1)
		{
			// Console Window
			HWND hConsole = GetConsoleWindow();
			RECT rect;
			GetWindowRect(hConsole, &rect);
			// Desktop
			HWND hDesktop = GetDesktopWindow();
			RECT rDesktopRect;
			GetWindowRect(hDesktop, &rDesktopRect);
			// Update Position
			SetWindowPos(hConsole, nullptr, rDesktopRect.right + 100, 150, rect.right - rect.left, rect.bottom - rect.top + 100, 0);
			//SetWindowPos(hConsole, nullptr, rDesktopRect.left - rDesktopRect.right, 150, rect.right - rect.left, rect.bottom - rect.top + 100, 0);
		}
	}

	void draw_current_Modelname()
	{
		char string[40];
		CVector posn = FindPlayerCoors(-1);
		posn.z = posn.z - 5;
		CColPoint colp;
		CEntity *entity = 0;
		CWorld::ProcessVerticalLine(posn, posn.z + 100.0f, colp, entity, true, false, false, false, false, false, false);
		if (entity != 0)
		{
			CFont::SetColor(CRGBA::CRGBA(200, 200, 200, 255));
			sprintf(string, " Model: %s", CFileLoader::Objectnamelist[entity->m_wModelIndex].mName);
			CFont::SetFontStyle(FONT_SUBTITLES);
			CFont::SetAlignment(ALIGN_LEFT);
			CFont::SetOutlinePosition(1);
			CFont::SetScale(CHud::x_fac(0.25f), CHud::y_fac(0.5f));
			CFont::PrintString(CHud::x_fac(15.0f), CHud::y_fac(5.0f), string);
		}
	}

	void draw_FPS()
	{
		char string[40];
		CFont::SetColor(CRGBA::CRGBA(200, 200, 200, 255));
		//sprintf(string, "FPS : %d", (int)CTimer::ms_gameFPS);
		
		sprintf(string, "FPS : %d", (int)CTimer::ms_gameFPS);
		//sprintf(string, "FPS : %d", (int)TheCamera.m_PlayerWeaponMode.m_wMode);
		//sprintf(string, "FPS : %d", (int)TheCamera.m_aCams[TheCamera.m_nActiveCam].m_eMode);
		//sprintf(string, "Radrmode : %f", (float)FrontEndMenuManager.m_dwRadarMode);

		CFont::SetFontStyle(FONT_SUBTITLES);
		CFont::SetAlignment(ALIGN_LEFT);
		CFont::SetOutlinePosition(1);
		CFont::SetScale(CHud::x_fac(0.25f), CHud::y_fac(0.5f));
		CFont::PrintString(CHud::x_fac(200.0f), CHud::y_fac(5.0f), string);

		/*sprintf(string, "zoom : %f", (float)FrontEndMenuManager.m_fMapZoom);
		CFont::PrintString(CHud::x_fac(15.0f), CHud::y_fac(15.0f),string);*/
	}

	void draw_graphics_info()
	{
		char string[40];
		CFont::SetColor(CRGBA::CRGBA(200, 200, 200, 255));
		sprintf(string, "max Anistropy : %d", (int)RpAnisotGetMaxSupportedMaxAnisotropy());
		CFont::SetFontStyle(FONT_SUBTITLES);
		CFont::SetAlignment(ALIGN_LEFT);
		CFont::SetOutlinePosition(1);
		CFont::SetScale(CHud::x_fac(0.25f), CHud::y_fac(0.5f));
		CFont::PrintString(CHud::x_fac(15.0f), CHud::y_fac(15.0f), string);
	}

	void DebugMenuInit(void)
	{
		if (DebugMenuLoad()) {
			DebugMenuProcess = (void(*)(void))GetProcAddress(gDebugMenuAPI.module, "DebugMenuProcess");
			DebugMenuRender = (void(*)(void))GetProcAddress(gDebugMenuAPI.module, "DebugMenuRender");
		}
		if (DebugMenuProcess == NULL || DebugMenuRender == NULL) {
			DebugMenuProcess = stub;
			DebugMenuRender = stub;
		}

	}

	void DebugMenuSetup()
	{

		if (DebugMenuLoad()) {
			DebugMenuInit();
		}
	}


}

