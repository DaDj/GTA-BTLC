#include "CMenuManager.h"
#include "CPad.h"
#include "CText.h"
#include "CFont.h"
#include "CTimer.h"
#include "RenderWare.h"
#include "../game_sa/CHud.h"
#include "CHudColours.h"
#include "common.h"
#include "CAERadioTrackManager.h"
#include "Fx_c.h"
#include "CCamera.h"
#include "../BTLC_BASE/windowmode/windowmode.h"
#include "CRadar.h"
#include "CFileMgr.h"
#include "CPcSave.h"
#include "CMenuSystem.h"
//#include "CAudioEngine.h"

MyDisplayoptions  CMenuManager::CustomOptions = { 0,800,600,0 };

MainMenuStrip  CMenuManager::MyMainMenu;
CRect CMenuManager::MainMenuMapRect = CRect::CRect();



CMenuManager &FrontEndMenuManager = *(CMenuManager *)0xBA6748;
CMenuPage	*MenuPages = (CMenuPage *)0x8CE008;

int CMenuManager::LikeALastSelectedMenuItem = 157;

bool& CMenuManager::bInvertMouseX = *(bool *)0xBA6744;
bool& CMenuManager::bInvertMouseY = *(bool *)0xBA6745;

int& CMenuManager::nLastMenuPage = *(int *)0x8CDFF0;

int& CMenuManager::ScanUserTracksProgressPos = *(int *)0x8CE000;
int& CMenuManager::ScanUserTracksProgressPosChange = *(int *)0x8CDFFC;
bool& CMenuManager::byte_8CDFFA = *(bool *)0x8CDFFA;
int& CMenuManager::dword_B6B988 = *(int *)0xB6B988;
int(*CMenuManager::Slotvalidation)[9] = (int(*)[9])0xC16EB8;



float CMenuManager::StretchX(float x)
{
	float width_fac = RsGlobal.maximumHeight / 448.0f;
	return x * width_fac;
}

float CMenuManager::StretchY(float y)
{
	float height_fac = RsGlobal.maximumHeight / 448.0f;
	return y * height_fac;
}


void CMenuManager::Initialise()
{

	m_nPlayerNumber = 0;
	field_1B1C = 0;
	m_dwSelectedMenuItem = 0;
	m_bSelectedSaveGame = 0;
	if (m_bChangeVideoMode)
	{
		RwD3D9ChangeMultiSamplingLevels(m_dwAppliedAntiAliasingLevel);
		RwEngineSetVideoMode(m_dwAppliedResolution);
		m_bChangeVideoMode = 0;
	}
	CentreMousePointer();
	field_8 = 3;
	m_fMapZoom = 270.0f;
	float temp = m_fMapBaseX - 1100.0f;
	if (temp > 0.0f)
		m_fMapBaseX = m_fMapBaseX - temp;

	temp = m_fMapBaseX + 1100.0f;
	if (temp < 640.0f)
		m_fMapBaseX = 640.0f - temp + m_fMapBaseX;

	temp = m_fMapBaseY - 1100.0f;
	if (temp > 0.0f)
		m_fMapBaseY = m_fMapBaseY - temp;

	temp = m_fMapBaseY + 1100.0f;
	if (temp > 0.0f)
		m_fMapBaseY = 448.0f - temp + m_fMapBaseY;

	CRadar::SetMapCentreToCoords(-10.0f, 550.0f);
	if (!field_F4)
	{
		m_nCurrentMenuPage = MENUPAGE_QUIT_GAME_2;
		m_bMapLoaded = 0;
		m_dwOldMousePosLeft = 0;
		m_dwOldMousePosTop = 0;
		m_bDrawMouse = 0;
	}
	CFileMgr::SetDir(gta_empty_string);
	CPcSave::PopulateSlotInfo();
	CTimer::StartUserPause();
	PanelID = -99;
	CAudioEngine::GetCurrentRadioStationID();
}



void CMenuManager::ProcessStreaming(char bImmediately)
{
	((void(__thiscall *)(CMenuManager*, char))0x573CF0)(this, bImmediately);
}

void CMenuManager::UserInput()
{

	//escape from the menu into the game from every page
	if (CPad::GetPad(0)->NewState.ButtonTriangle && !CPad::GetPad(0)->OldState.ButtonTriangle ||
		CPad::NewKeyState.esc && !CPad::OldKeyState.esc)
	{
		if (m_nCurrentMenuPage == MENUPAGE_MAP ||
			m_nCurrentMenuPage == MENUPAGE_BRIEF ||
			m_nCurrentMenuPage == MENUPAGE_AUDIO_SETTINGS ||
			m_nCurrentMenuPage == MENUPAGE_DISPLAY_SETTINGS ||
			m_nCurrentMenuPage == MENUPAGE_START_GAME ||
			m_nCurrentMenuPage == MENUPAGE_DISPLAY_ADVANCED ||
			m_nCurrentMenuPage == MENUPAGE_MAIN_MENU ||
			m_nCurrentMenuPage == MENUPAGE_CONTROLLER_SETUP)
		{
			if (!m_bMainMenuSwitch)
			{
				m_bDrawMouse = 0;
				m_bActivateMenuNextFrame = 0;
				m_bDontDrawFrontEnd = 1;
				//m_bMenuActive = 0;
				return;
			}

		}

	}


	//check if game has already loaded(different menus)
	if (m_bMainMenuSwitch)
		MyMainMenu.m_nActiveMenu = 1;
	else
		MyMainMenu.m_nActiveMenu = 0;



	//check if main mneu is hovered and process it
	MyMainMenu.m_nHoverItem = -1;
	if (m_dwMousePosTop <= StretchY(60))
	{
		m_bDrawMouse = 1;
		m_dwOldMousePosLeft = CPad::NewMouseControllerState.X;
		m_dwOldMousePosTop = CPad::NewMouseControllerState.Y;
		m_dwMousePosLeft = mousePosLeft_NotClipped;
		m_dwMousePosTop = mousePosTop_NotClipped;
		float MultRes = 1;
		float Resfac = ((float)RsGlobal.maximumWidth / (float)RsGlobal.maximumHeight);
		if (Resfac <= 1.63f)
		{
			CFont::SetScale(StretchX(0.45), StretchY(0.45));
			MultRes = 0.8;
			if (Resfac <= 1.5f)
				MultRes = 0.6;
		}

		for (int i = 0; i < 12; i++)
		{
			if (MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_szName[0])
			{
				if (m_dwMousePosLeft > StretchX(MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_wPosnX - 50)*MultRes && m_dwMousePosLeft < StretchX(MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_wPosnX + 50)*MultRes)
				{
					MyMainMenu.m_nHoverItem = i;
					if (CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
					{
						m_nCurrentMenuPage = MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_nTargetMenu;
						AudioEngine.ReportFrontendAudioEvent(1, 0.0, 1.0);
					}
				}

			}
		}

	}
	else
	{
		((void(__thiscall *)(CMenuManager*))0x57FD70)(this);
	}


	//	CMenuManager ThisMenuManager; // esi
	//	//char DrawMouse; // al
	//	//int v4; // ecx
	//	//int v5; // eax
	//	char selectedItem; // bl
	//	//int v7; // ecx
	//	//int v8; // edi
	//	int v9; // eax
	//	//char v10; // cl
	//	char *v11; // eax
	//	int v12; // eax
	//	float v13; // ST08_4
	//	//float v14; // ST18_4
	//	//float v15; // ST08_4
	//	//int v16; // eax
	//	//int v17; // ecx
	//	//int v18; // ecx
	//	//int v19; // edx
	//	//int v20; // eax
	//	//int v21; // edx
	//	//int v22; // ecx
	//	//int v23; // eax
	//	//Pad *v24; // eax
	//	//CPad *v25; // eax
	//	char v26; // bl
	//	CPad *v27; // eax
	//	CPad *v28; // eax
	//	//CPad *v29; // eax
	//	char v30; // al
	//	//CPad *v31; // eax
	//	//CPad *v32; // eax
	//	char v33; // al
	//	int v34; // [esp-8h] [ebp-30h]
	//	char v35; // [esp+0h] [ebp-28h]
	//	char wheel; // [esp+10h] [ebp-18h]
	//	int bEnter = 0; // [esp+14h] [ebp-14h]
	//	int bExit = 0; // [esp+18h] [ebp-10h]
	//	int bUp = 0; // [esp+1Ch] [ebp-Ch]
	//	int bDown = 0; // [esp+20h] [ebp-8h]
	//	float v41; // [esp+24h] [ebp-4h]
	//	CPad *CPad0 = CPad::GetPad(0);
	//
	//	//ThisMenuManager = *this;
	//	if (m_bScanningUserTracks || field_1AEA)
	//		return;
	//
	//	if (!m_bDrawMouse && m_dwOldMousePosLeft && m_dwOldMousePosTop)
	//	{
	//		if (m_dwOldMousePosLeft != m_dwMousePosLeft || m_dwOldMousePosTop != m_dwMousePosTop)
	//			m_bDrawMouse = 1;
	//	}
	//
	//	LikeALastSelectedMenuItem = m_dwSelectedMenuItem;
	//	selectedItem = 0;
	//	while (1)
	//	{
	//		if (MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_nActionType &&
	//			MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_nActionType != MENU_ACTION_TEXT)
	//		{
	//			break;
	//		}
	//	LABEL_16:
	//		if (++selectedItem >= 12)
	//			goto MENU_ITEM_CHANGED;
	//	}
	//	//CFont::GetStringWidth(TheText.Get(MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_szName), 1, 0);
	//
	//	// If current menu NOT active!!
	//	if (CHud::y_fac(MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_wPosnY) >= m_dwMousePosTop
	//		|| CHud::y_fac(MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_wPosnY + 26) <= m_dwMousePosTop)
	//	{
	//		if (m_bDrawMouse)
	//		{
	//			field_1B04 = LikeALastSelectedMenuItem;
	//			m_dwSelectedMenuItem = LikeALastSelectedMenuItem;
	//		}
	//		goto LABEL_16;
	//	}
	//	if (!(field_1B74 & 1))
	//	{
	//		field_1B74 |= 1u;
	//		field_1B70 = m_nCurrentMenuPage;
	//	}
	//	//byte_8CE004 = v2->field_1B04;
	//	field_1B04 = selectedItem;
	//	if (m_dwOldMousePosLeft && m_dwOldMousePosTop)
	//	{
	//		if (m_dwOldMousePosLeft != m_dwMousePosLeft || m_dwOldMousePosTop != m_dwMousePosTop)
	//		{
	//			m_dwSelectedMenuItem = selectedItem;
	//			m_bDrawMouse = 1;
	//		}
	//	}
	//	switch (MenuPages[m_nCurrentMenuPage].m_aButtons[selectedItem].m_nActionType)
	//	{
	//	case MENU_ACTION_SLIDER_BRIGHTNESS:
	//	case MENU_ACTION_SLIDER_MUSIC:
	//	case MENU_ACTION_SLIDER_SFX:
	//	case MENU_ACTION_SLIDER_LOD:
	//	case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
	//		break;
	//	default:
	//		bSlidingType = 2;
	//		break;
	//	}
	//MENU_ITEM_CHANGED:
	//
	//	if (m_bDrawMouse && LikeALastSelectedMenuItem != m_dwSelectedMenuItem)
	//	{
	//		if (MenuPages[m_nCurrentMenuPage].m_aButtons[m_dwSelectedMenuItem].m_nActionType == MENU_ACTION_TEXT)
	//		{
	//			m_dwSelectedMenuItem++;
	//			++field_1B04;
	//		}
	//		AudioEngine.ReportFrontendAudioEvent(3, 0.0, 1.0);
	//	}
	//	// update mouse posn
	//
	//	m_dwOldMousePosTop = m_dwMousePosTop;
	//	m_dwOldMousePosLeft = m_dwMousePosLeft;
	//	m_dwMousePosLeft = mousePosLeft_NotClipped;
	//	m_dwMousePosTop = mousePosTop_NotClipped;
	//	if (m_dwMousePosLeft < 0)
	//		m_dwMousePosLeft = 0;
	//	if (m_dwMousePosLeft > RsGlobal.maximumWidth)
	//		m_dwMousePosLeft = RsGlobal.maximumWidth;
	//	if (m_dwMousePosTop < 0)
	//		m_dwMousePosTop = 0;
	//	if (m_dwMousePosTop > RsGlobal.maximumHeight)
	//		m_dwMousePosTop = RsGlobal.maximumHeight;
	//	wheel = 0;
	//
	//	if (m_nCurrentMenuPage == MENUPAGE_CONTROLS_VEHICLE_ONFOOT)
	//	{
	//		if (!field_1AEA)
	//			RedefineScreenUserInput(bEnter,bExit);
	//		goto LABEL_113;
	//	}
	//	if (GetNumberOfMenuOptions() > 1)
	//	{
	//		AdditionalOptionInput(bUp, bDown);
	//		if (CheckFrontEndDownInput())
	//			bDown = 1;
	//		else if (CheckFrontEndUpInput())
	//			bUp = 1;
	//		m_bDrawMouse = 0;
	//	}
	//	if (m_dwSelectedMenuItem || m_nCurrentMenuPage != MENUPAGE_PAUSE_MENU)
	//	{
	//		if ((CPad::NewKeyState.enter && !CPad::OldKeyState.enter
	//			|| CPad::NewKeyState.extenter && !CPad::OldKeyState.extenter)
	//			&& field_30 < 0
	//			|| CPad0->NewState.ButtonCross && !CPad0->OldState.ButtonCross)
	//		{
	//			m_bDrawMouse = 0;
	//			bEnter = 1;
	//		}
	//	}
	//	else if ((!CPad::NewKeyState.enter && CPad::OldKeyState.enter
	//		|| !CPad::NewKeyState.extenter && CPad::OldKeyState.extenter)
	//		&& field_30 < 0
	//		|| !CPad0->NewState.ButtonCross && CPad0->OldState.ButtonCross)
	//	{
	//		m_bDrawMouse = 0;
	//		bEnter = 1;
	//	}
	//
	//
	//	CPad::GetPad(0);
	//	if (!CPad::NewMouseControllerState.lmb && CPad::OldMouseControllerState.lmb && bSlidingType == 2)
	//	{
	//		if (m_nCurrentMenuPage == MENUPAGE_MAP
	//			&& CHud::y_fac(388.0) < m_dwMousePosTop
	//			|| m_bDrawMouse)
	//		{
	//			//v41 = m_dwMousePosTop;
	//			bEnter = 1;
	//		}
	//	}
	//	v26 = CPad::NewMouseControllerState.lmb;
	//	CPad::GetPad(0);
	//	if (v26)
	//	{
	//		switch (bSlidingType)
	//		{
	//		case 6:
	//		case 8:
	//		case 10:
	//		case 12:
	//		case 14:
	//			v35 = 1;
	//			goto LABEL_79;
	//		case 7:
	//		case 9:
	//		case 11:
	//		case 13:
	//		case 15:
	//			v35 = -1;
	//		LABEL_79:
	//			CheckSliderMovement(v35);
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//	CPad::GetPad(0);                              // left right sets?
	//	if (CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
	//		goto LABEL_151;
	//	CPad::GetPad(0);
	//	if (CPad::NewKeyState.left)
	//	{
	//		if (!CPad::OldKeyState.left)
	//			goto LABEL_151;
	//	}
	//	if ((CPad::GetPad(0), CPad::NewKeyState.right) && !CPad::OldKeyState.right
	//		|| (v27 = CPad::GetPad(0), v27->NewState.DPadLeft) && !v27->OldState.DPadLeft
	//		|| (v28 = CPad::GetPad(0), (unsigned __int8)sub_4410E0((int)v28))
	//		|| (CPad::GetPad(0), sub_5409B0())
	//		|| (CPad::GetPad(0), sub_5409E0())
	//		|| (CPad::GetPad(0), sub_57C400())
	//		|| (CPad::GetPad(0), sub_57C420()))
	//	{
	//	LABEL_151:
	//		switch (MenuPages[m_nCurrentMenuPage].m_aButtons[m_dwSelectedMenuItem].m_nActionType)
	//		{
	//		case 27:
	//		case 28:
	//		case 61:
	//		case 62:
	//			v34 = 1;
	//			goto LABEL_96;
	//		case 29:
	//			v34 = 5;
	//		LABEL_96:
	//			AudioEngine.ReportFrontendAudioEvent(v34, 0.0, 1.0);
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//	v29 = CPad::GetPad(0);
	//	if (v29->NewState.ButtonTriangle && !v29->OldState.ButtonTriangle
	//		|| (CPad::GetPad(0), CPad::NewKeyState.esc) && !CPad::OldKeyState.esc)
	//	{
	//		v30 = m_nCurrentMenuPage;
	//		if (v30 != MENUPAGE_MAIN_MENU
	//			&& v30 != MENUPAGE_PAUSE_MENU
	//			&& v30 != MENUPAGE_GAME_SAVE
	//			&& v30 != MENUPAGE_GAME_WARNING_DONT_SAVE
	//			&& v30 != MENUPAGE_SAVE_DONE_1
	//			&& v30 != MENUPAGE_DELETE_FINISHED
	//			&& v30 != MENUPAGE_EMPTY)
	//		{
	//			m_bDrawMouse = 0;
	//			bExit = 1;
	//		}
	//	}
	//	if (bDown || bUp || bEnter)
	//		bExit = 0;
	//LABEL_113:
	//	if (CPad::NewKeyState.left
	//		|| CPad::GetPad(0)->GetPedWalkLeftRight() < 0
	//		|| CPad::GetPad(0)->NewState.DPadLeft)
	//	{
	//		if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - m_dwTimeSlideLeftMove) > 200)
	//		{
	//			switch (MenuPages[m_nCurrentMenuPage].m_aButtons[m_dwSelectedMenuItem].m_nActionType)
	//			{
	//			case MENU_ACTION_STATS:
	//			case MENU_ACTION_SLIDER_BRIGHTNESS:
	//			case MENU_ACTION_SLIDER_MUSIC:
	//			case MENU_ACTION_SLIDER_SFX:
	//			case MENU_ACTION_SLIDER_LOD:
	//			case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
	//				wheel = -1;
	//				break;
	//			default:
	//				break;
	//			}
	//			ThisMenuManager.m_dwTimeSlideLeftMove = CTimer::m_snTimeInMillisecondsPauseMode;
	//		}
	//	}
	//	else
	//	{
	//		CPad::GetPad(0);
	//		if (CPad::NewKeyState.right
	//			|| CPad::GetPad(0)->GetPedWalkLeftRight() > 0
	//			|| CPad::GetPad(0)->NewState.DPadRight)
	//		{
	//			if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - ThisMenuManager.m_dwTimeSlideRightMove) > 200)
	//			{
	//				switch (eMenuActions(MenuPages[m_nCurrentMenuPage].m_aButtons[m_dwSelectedMenuItem].m_nActionType))
	//				{
	//				case MENU_ACTION_STATS:
	//				case MENU_ACTION_SLIDER_BRIGHTNESS:
	//				case MENU_ACTION_SLIDER_MUSIC:
	//				case MENU_ACTION_SLIDER_SFX:
	//				case MENU_ACTION_SLIDER_LOD:
	//				case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
	//					wheel = 1;
	//					break;
	//				default:
	//					break;
	//				}
	//				ThisMenuManager.m_dwTimeSlideRightMove = CTimer::m_snTimeInMillisecondsPauseMode;
	//			}
	//		}
	//	}
	//	CPad::GetPad(0);
	//	if (!CPad::NewMouseControllerState.wheelUp || CPad::OldMouseControllerState.wheelUp)
	//	{
	//		CPad::GetPad(0);
	//		if (CPad::NewMouseControllerState.wheelDown
	//			&& !CPad::OldMouseControllerState.wheelDown
	//			&& m_nCurrentMenuPage != MENUPAGE_MAP)
	//		{
	//			wheel = -1;
	//		}
	//	}
	//	else if (m_nCurrentMenuPage != MENUPAGE_MAP)
	//	{
	//		wheel = 1;
	//	}
	//	if (CheckFrontEndRightInput())
	//	{
	//		m_bDrawMouse = 0;
	//		wheel = 1;
	//		goto LABEL_140;
	//	}
	//	if (CheckFrontEndLeftInput())
	//	{
	//		m_bDrawMouse = 0;
	//		wheel = -1;
	//		goto LABEL_140;
	//	}
	//	if (wheel)
	//	{
	//	LABEL_140:
	//		if (m_nCurrentMenuPage == MENUPAGE_AUDIO_SETTINGS
	//			|| m_nCurrentMenuPage == MENUPAGE_USER_TRACKS_OPTIONS
	//			|| m_nCurrentMenuPage == MENUPAGE_DISPLAY_SETTINGS
	//			|| m_nCurrentMenuPage == MENUPAGE_DISPLAY_ADVANCED
	//			|| m_nCurrentMenuPage == MENUPAGE_CONTROLLER_SETUP
	//			|| m_nCurrentMenuPage == MENUPAGE_MOUSE_SETTINGS)
	//		{
	//			switch (MenuPages[v33].m_aButtons[m_dwSelectedMenuItem].m_nActionType)
	//			{
	//			case MENU_ACTION_BACK:
	//			case MENU_ACTION_SWITCH:
	//			case MENU_ACTION_CONFIGURATIONINPUT:
	//			case MENU_ACTION_FOOTCONTROLs:
	//			case MENU_ACTION_VEHICLECONTROLS:
	//			case MENU_ACTION_SLIDER_BRIGHTNESS:
	//			case MENU_ACTION_SLIDER_MUSIC:
	//			case MENU_ACTION_SLIDER_SFX:
	//			case MENU_ACTION_RADIOSTATION:
	//			case MENU_ACTION_RESETSETTINGS:
	//			case MENU_ACTION_SLIDER_LOD:
	//			case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
	//				break;
	//			default:
	//				AudioEngine.ReportFrontendAudioEvent(1, 0.0, 1.0);
	//				break;
	//			}
	//		}
	//	}
	//	ProcessUserInput(bDown, bUp, bEnter, bExit, wheel);
}


void CMenuManager::RedefineScreenUserInput(int enter, int exit)
{
	((void(__thiscall *)(CMenuManager*, int, int))0x57EF50)(this, enter, exit);
}

int CMenuManager::GetNumberOfMenuOptions()
{
	return ((int(__thiscall *)(CMenuManager*))0x573E70)(this);
}

int CMenuManager::AdditionalOptionInput(int bUp, int bDown)
{
	return ((int(__thiscall *)(CMenuManager*, int, int))0x5773D0)(this, bUp, bDown);
}

bool CMenuManager::CheckFrontEndDownInput()
{
	return	((bool(__thiscall *)(CMenuManager*))0x5738B0)(this);
}

bool CMenuManager::CheckFrontEndUpInput()
{
	return	((bool(__thiscall *)(CMenuManager*))0x573840)(this);
}

bool CMenuManager::CheckFrontEndRightInput()
{
	return	((bool(__thiscall *)(CMenuManager*))0x573990)(this);
}

bool CMenuManager::CheckFrontEndLeftInput()
{
	return	((bool(__thiscall *)(CMenuManager*))0x573920)(this);
}

void CMenuManager::CheckSliderMovement(char count)
{
	((void(__thiscall *)(CMenuManager*, char))0x573440)(this, count);
}

void CMenuManager::CentreMousePointer()
{
	((void(__cdecl *)())0x57C520)();
}

void CMenuManager::ProcessUserInput(char bDown, char bUp, char bEnter, char bExit, char wheel)
{
	((void(__thiscall *)(CMenuManager*, char, char, char, char, char))0x57B480)(this, bDown, bUp, bEnter, bExit, wheel);
}

void CMenuManager::DrawBackground()
{
	int SpriteID;
	if (!m_bTexturesLoaded)
		return;
	switch (m_nCurrentMenuPage)
	{
	case MENUPAGE_STATS:
	case MENUPAGE_LANGUAGE:
	case MENUPAGE_QUIT_GAME_ASK:
	case MENUPAGE_MAIN_MENU:
	case MENUPAGE_PAUSE_MENU:
		SpriteID = 15;
		break;
	case MENUPAGE_START_GAME:
	case MENUPAGE_USER_TRACKS_OPTIONS:
	case MENUPAGE_OPTIONS:
		SpriteID = 14;
		break;
	case MENUPAGE_BRIEF:
	case MENUPAGE_LOAD_GAME:
	case MENUPAGE_DELETE_GAME:
	case MENUPAGE_GAME_SAVE:
		SpriteID = 13;
		break;
	case MENUPAGE_AUDIO_SETTINGS:
		SpriteID = 13;
		break;
	case MENUPAGE_DISPLAY_SETTINGS:
	case MENUPAGE_DISPLAY_ADVANCED:
		SpriteID = 18;
		break;
	case MENUPAGE_MAP:
	case MENUPAGE_CONTROLS_VEHICLE_ONFOOT:
		SpriteID = 0;
		break;
	case MENUPAGE_CONTROLLER_SETUP:
	case MENUPAGE_MOUSE_SETTINGS:
		SpriteID = 17;
		break;
	default:
		SpriteID = 0;
		break;
	}


	CRect BackgrndRect;
	BackgrndRect.m_fLeft = 0;
	BackgrndRect.m_fRight = RsGlobal.maximumWidth;
	BackgrndRect.m_fTop = 0;
	BackgrndRect.m_fBottom = RsGlobal.maximumHeight;
	CSprite2d::DrawRect(BackgrndRect, CRGBA::CRGBA(20, 20, 20, 255));



	FrontEndMenuManager.m_nBackgroundSprite = SpriteID;
	if (m_nBackgroundSprite)
	{
		//Letterbox crop for background
		float Ratio = RsGlobal.maximumWidth / RsGlobal.maximumHeight;
		float goalwidth = 1.77 * RsGlobal.maximumHeight;
		float goalheight = RsGlobal.maximumWidth / 1.77;

		if (RsGlobal.maximumWidth > goalwidth)
		{
			float heightdiff = RsGlobal.maximumHeight - goalheight;
			BackgrndRect.m_fTop = heightdiff;
			BackgrndRect.m_fLeft = 2.0f;
		}
		else if (RsGlobal.maximumHeight > goalheight)
		{
			float widthdiff = RsGlobal.maximumWidth - goalwidth;
			BackgrndRect.m_fTop = 2.0f;
			BackgrndRect.m_fLeft = widthdiff;
		}
		else
		{
			BackgrndRect.m_fLeft = 0.0f;
			BackgrndRect.m_fTop = 1.0f;
		}


		BackgrndRect.m_fRight = RsGlobal.maximumWidth;
		BackgrndRect.m_fBottom = RsGlobal.maximumHeight;
		FrontEndMenuManager.m_apBackgroundTextures[SpriteID - 13].Draw(BackgrndRect, CRGBA::CRGBA(100, 100, 100, 255));
	}
	

	/*CRect Contentcrect;
	Contentcrect.m_fLeft = StretchX(10);
	Contentcrect.m_fRight = RsGlobal.maximumWidth - StretchX(10);
	Contentcrect.m_fTop = StretchY(90);
	Contentcrect.m_fBottom = RsGlobal.maximumHeight - StretchY(90);
	CSprite2d::DrawRect(Contentcrect, CRGBA::CRGBA(0, 0, 0, 80));
*/
	if (m_nCurrentMenuPage == MENUPAGE_MAP)
	{
		float tmpMapBaseX = m_fMapBaseX;
		float tmpMapZoom = m_fMapZoom;
		float tmpMapBaseY = m_fMapBaseY;
		PrintMap();
		m_fMapBaseX = tmpMapBaseX;
		m_fMapZoom = tmpMapZoom;
		m_fMapBaseY = tmpMapBaseY;
	}
	if (m_nCurrentMenuPage == MENUPAGE_CONTROLS_VEHICLE_ONFOOT)
		DrawControllerSetupScreen();
	else if (m_nCurrentMenuPage == MENUPAGE_EMPTY)
		DrawQuitGameScreen();
	else
		DrawStandardMenus(1);

	if (IsKeyUnbound)
	{
		char* Text;

		if (!(field_1B4C & 1))
		{
			field_1B4C |= 1u;
			m_dwMAYBEKeyDelay = CTimer::m_snTimeInMillisecondsPauseMode;
		}
		if (FrontEndMenuManager.m_bExitMenu)
		{
			m_dwMAYBEKeyDelay = CTimer::m_snTimeInMillisecondsPauseMode;
			m_bExitMenu = 0;
		}

		if (RwCameraBeginUpdate(Scene.m_pRwCamera))
		{
			if (IsKeyUnbound == 1)
				Text = "FEC_ER3"; //vehicle unbounded onf foot control
			else if (IsKeyUnbound == 2)
				Text = "FEC_ER2"; //foot unbounded vehicle control
			else
				Text = "FEC_ERI"; //some key not bound

			CSprite2d::SetRecipNearClip();
			CSprite2d::InitPerFrame();
			CFont::InitPerFrame();
			DefinedState2d();
			CMenuManager::SmallMessageScreen(Text);
			CFont::DrawFonts();
		}

		CFont::DrawFonts();
		if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - FrontEndMenuManager.m_dwMAYBEKeyDelay) > 7000
			|| CPad::NewKeyState.esc && !CPad::OldKeyState.esc
			&& (unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - FrontEndMenuManager.m_dwMAYBEKeyDelay) > 1000)
		{
			IsKeyUnbound = 0;
			FrontEndMenuManager.m_bExitMenu = 1;
		}
		return;
	}


	//User Tracks Scanning Message
	if (m_bScanningUserTracks)
	{
		if (!(FrontEndMenuManager.field_1B4C & 2))
		{
			FrontEndMenuManager.field_1B4C |= 2u;
			FrontEndMenuManager.field_1B40 = CTimer::m_snTimeInMillisecondsPauseMode;
		}
		if (RwCameraBeginUpdate(Scene.m_pRwCamera))
		{
			CSprite2d::SetRecipNearClip();
			CSprite2d::InitPerFrame();
			CFont::InitPerFrame();
			DefinedState2d();
			CMenuManager::SmallMessageScreen("FEA_SMP");// SCANNING USER TRACKS - PLEASE WAIT~n~~n~Press ESC to cancel
			CFont::DrawFonts();
		}
		if (CTimer::m_FrameCounter & 4)
		{
			ScanUserTracksProgressPos -= ScanUserTracksProgressPosChange; //Usertracksearchbar

			if (ScanUserTracksProgressPos >= RsGlobal.maximumWidth / 2 + StretchX(50))
				ScanUserTracksProgressPosChange = StretchX(1);

			if (ScanUserTracksProgressPos <= RsGlobal.maximumWidth / 2 - StretchX(50))
			{
				ScanUserTracksProgressPos = RsGlobal.maximumWidth / 2 - StretchX(50);
				ScanUserTracksProgressPosChange = StretchX(-1);
			}

		}
		CRect LoadbarBgrndRect;
		LoadbarBgrndRect.m_fLeft = RsGlobal.maximumWidth / 2 - StretchX(50);
		LoadbarBgrndRect.m_fTop = RsGlobal.maximumHeight / 2 + StretchY(26);
		LoadbarBgrndRect.m_fRight = RsGlobal.maximumWidth / 2 + StretchX(50);
		LoadbarBgrndRect.m_fBottom = RsGlobal.maximumHeight / 2 + StretchY(32);
		CSprite2d::DrawRect(LoadbarBgrndRect, CRGBA::CRGBA(50, 50, 50, 255));


		CRect RectLoadBar;
		RectLoadBar.m_fLeft = ScanUserTracksProgressPos;
		RectLoadBar.m_fTop = RsGlobal.maximumHeight / 2 + StretchY(26);
		RectLoadBar.m_fRight = ScanUserTracksProgressPos + StretchX(5);
		RectLoadBar.m_fBottom = RsGlobal.maximumHeight / 2 + StretchY(32);
		CSprite2d::DrawRect(RectLoadBar, CRGBA::CRGBA(225, 225, 225, 255));
		CFont::DrawFonts();
		int v56 = 0;
		ResetHelperText();
		if (byte_8CDFFA)
		{
			FrontEndMenuManager.field_1B40 = CTimer::m_snTimeInMillisecondsPauseMode;
			byte_8CDFFA = 0;
		}
		if (UtraxThreadDesc.startUtraxThread(5)
			|| CPad::NewKeyState.esc && !CPad::OldKeyState.esc)
		{
			if ((unsigned int)(CTimer::m_snTimeInMillisecondsPauseMode - FrontEndMenuManager.field_1B40) > 3000
				|| CPad::NewKeyState.esc && !CPad::OldKeyState.esc)
			{
				if (dword_B6B988 >= 2)
				{
					if (dword_B6B988 == 2) //v28
					{
						if (!CPad::NewKeyState.esc && !CPad::OldKeyState.esc)
						{
							UtraxThreadDesc.loadUtrax();
							v56 = 5;
							FrontEndMenuManager.m_bScanningUserTracks = 0;
							byte_8CDFFA = 1;
							SetHelperText(v56);
							CMenuManager::DisplayHelperText(0);
							return;
						}
					}
					if (dword_B6B988 <= 3)
						dword_B6B988 = 0;
				}

				if (dword_B6B988 == 3) //v29
				{
					v56 = 4;
				}
				else if (dword_B6B988 >= 2 && !dword_B6B988 > 3)
				{
					dword_B6B988 = 0;
				}
				if (!CPad::NewKeyState.esc && !CPad::OldKeyState.esc)
				{
					CMenuManager::DisplayHelperText(0);
					return;
				}
				v56 = 4;
				FrontEndMenuManager.m_bScanningUserTracks = 0;
				byte_8CDFFA = 1;
				SetHelperText(v56);
				CMenuManager::DisplayHelperText(0);
				return;
			}
		}
	}

	// Draw Mouse
	if (m_bDrawMouse)
	{
		int MapTop = StretchY(0.0f);
		int MaptBottom = RsGlobal.maximumHeight - StretchY(0.0f);
		int Mapleft = StretchX(0.0f);
		int MapRight = RsGlobal.maximumWidth - StretchX(0.0f);

		CFont::RenderFontBuffer();
		if (m_nCurrentMenuPage == MENUPAGE_MAP
			&& CPad::GetPad(m_nPlayerNumber)->NewMouseControllerState.lmb
			&& m_dwMousePosLeft > Mapleft && m_dwMousePosLeft < MapRight
			&& m_dwMousePosTop > MapTop && m_dwMousePosTop < MaptBottom)
		{
			CRect MouseRect;
			MouseRect.m_fLeft = m_dwMousePosLeft;
			MouseRect.m_fRight = MouseRect.m_fLeft + StretchX(15.0f);
			MouseRect.m_fTop = m_dwMousePosTop;
			MouseRect.m_fBottom = MouseRect.m_fTop + StretchY(15.0f);
			m_apMouseTextures[1].Draw(MouseRect, CRGBA::CRGBA(255, 255, 255, 255));
		}
		else
		{
			CRect MouseRect;
			MouseRect.m_fLeft = m_dwMousePosLeft;
			MouseRect.m_fRight = MouseRect.m_fLeft + StretchX(20.0f);
			MouseRect.m_fTop = m_dwMousePosTop;
			MouseRect.m_fBottom = MouseRect.m_fTop + StretchY(20.0f);
			m_apMouseTextures[0].Draw(MouseRect, CRGBA::CRGBA(255, 255, 255, 255));
		}
	}
}

char CMenuManager::PrintMap()
{
	//return	((char(__thiscall *)(CMenuManager*))0x575130)(this);

	//Check if Overvbiewmap should be displayed
	//CPad::GetPad(m_nPlayerNumber);
	//if (CPad::NewKeyState.standardKeys[90]	|| (CPad::GetPad(m_nPlayerNumber),CPad::NewKeyState.standardKeys[122]))
	//{
	//	DrawNormalRadarMap = false;
	//	m_bDrawMouse = false;
	//	
	//}

	drawRadarOrMap = true;
	CRadar::InitFrontEndMap();


	// Display Overview map
	//if (!DrawNormalRadarMap)
	//{
	//	if (PanelID >= 0)
	//	{
	//		CMenuSystem::SwitchOffMenu(PanelID);
	//		PanelID = 157;
	//	}
	//	m_fMapBaseX = 320.0f;
	//	m_fMapBaseY = 206.0f;
	//	m_fMapZoom = 140.0f;
	//	CVector WorldPos = FindPlayerCentreOfWorld_NoSniperShift(0);
	//	CVector2D Pos_in;
	//	Pos_in.x = WorldPos.x;
	//	Pos_in.y = WorldPos.y;
	//	CVector2D MapRecPos;
	//	CRadar::TransformRealWorldPointToRadarSpace(MapRecPos, Pos_in);
	//	CRadar::LimitRadarPoint(MapRecPos);
	//	Pos_in = MapRecPos;
	//	CRadar::TransformRadarPointToScreenSpace(MapRecPos, Pos_in);

	//	//calculate the mapzoom depending on the current pos somehow?
	//	float Tmp_Posx = m_fMapBaseX + 140.0f;
	//	float Tmp_posy = m_fMapBaseY + 140.0f;
	//	if (MapRecPos.x <= Tmp_Posx)
	//	{
	//		if (MapRecPos.y <= Tmp_posy)
	//		{
	//			Tmp_Posx = m_fMapBaseX - 140.0f;
	//			if (MapRecPos.x >= Tmp_Posx)
	//			{
	//				Tmp_posy = m_fMapBaseY - 140.0f;
	//				if (MapRecPos.y < Tmp_posy)
	//					m_fMapZoom = m_fMapZoom - (Tmp_posy - MapRecPos.y);
	//			}
	//			else
	//			{
	//				m_fMapZoom = m_fMapZoom - (Tmp_Posx - MapRecPos.x);
	//			}
	//		}
	//		else
	//			m_fMapZoom = m_fMapZoom - (Tmp_posy - MapRecPos.y);
	//	}
	//	else
	//	m_fMapZoom = m_fMapZoom - (Tmp_Posx - MapRecPos.x);


	//	//Limit minimal zoom to 70.0f ist limited to 270.0f in other fucntions anyway...
	//	if (m_fMapZoom < 70.0f)
	//		m_fMapZoom = 70.0f;
	//}



	float MapzoomMultiplierX = RsGlobal.maximumWidth*m_fMapZoom  * 0.16666* 0.0015625;
	float MapzoomMultiplierY = m_fMapZoom * 0.16666 *RsGlobal.maximumHeight  * 0.00223214;


	float x1 = MainMenuMapRect.m_fLeft = 0;
	float x2 = MainMenuMapRect.m_fRight =   RsGlobal.maximumWidth ;
	float y1 = MainMenuMapRect.m_fTop =  StretchY(0.0f);
	float y2 = MainMenuMapRect.m_fBottom = RsGlobal.maximumHeight - StretchY(0.0f);
	float TmpMapBasezoomX =  RsGlobal.maximumWidth* 0.0015625 *(m_fMapBaseX - m_fMapZoom);// StretchX(m_fMapBaseX - m_fMapZoom); /
	float TmpMapBasezoomY = RsGlobal.maximumHeight*  0.002232143 *(m_fMapBaseY - m_fMapZoom); // StretchY(m_fMapBaseY - m_fMapZoom); //



	if (m_bMapLoaded)
	{
		if (field_5A && !m_bAllStreamingStuffLoaded)
		{
			m_nMapTimer = CTimer::m_snTimeInMillisecondsPauseMode;
			m_bUpdateMap = 0;
		}

		if (CTimer::m_snTimeInMillisecondsPauseMode - m_nMapTimer > 150)
			m_bUpdateMap = 1;

	}
	else
	{
		m_nMapTimer = CTimer::m_snTimeInMillisecondsPauseMode;
		m_bUpdateMap = 0;
	}

	//BLue Background
	CSprite2d::DrawRect(CRect::CRect(0, 0, RsGlobal.maximumWidth, RsGlobal.maximumHeight), CRGBA::CRGBA(95, 125, 148, 255));
	if (m_bMapLoaded)
	{
		if (m_bAllStreamingStuffLoaded)
			field_5A = false;

		if (m_bUpdateMap && !m_bAllStreamingStuffLoaded)
		{
		
			
			for ( int iA = 0; iA < 12; iA++)
			{
				for (int iB = 0; iB < 12; iB++)
				{
				
					if (x1 - MapzoomMultiplierX < iA * MapzoomMultiplierX + TmpMapBasezoomX)
					{
						if (y1 - MapzoomMultiplierY < iB * MapzoomMultiplierY + TmpMapBasezoomY)
						{
							if (x2 + MapzoomMultiplierX > (iA + 1) * MapzoomMultiplierX + TmpMapBasezoomX)
							{
								if (y2 + MapzoomMultiplierY > (iB + 1) * MapzoomMultiplierY + TmpMapBasezoomY)
								{
									CRect MyRadarRect = CRect::CRect();
									MyRadarRect.m_fLeft = MapzoomMultiplierX * (iA) +  TmpMapBasezoomX;
									MyRadarRect.m_fRight = MapzoomMultiplierX * (iA+1) +  TmpMapBasezoomX;
									MyRadarRect.m_fTop = MapzoomMultiplierY * (iB) +  TmpMapBasezoomY;
									MyRadarRect.m_fBottom = MapzoomMultiplierY * (iB+1) +  TmpMapBasezoomY;
									CRadar::DrawRadarSectionMap(iA, iB, MyRadarRect);
								}
							}
						}
					}
				}

			
			}
		
		
			
			//CSprite2d::DrawRect(CRect::CRect(StretchX(60.0f), RsGlobal.maximumHeight - StretchY(60.0f), RsGlobal.maximumWidth- StretchX(60.0f) , RsGlobal.maximumHeight), CRGBA::CRGBA(0, 0, 0, 100));
			//CSprite2d::DrawRect(CRect::CRect(0, StretchY(60.0f), StretchX(60.0f), RsGlobal.maximumHeight), CRGBA::CRGBA(0, 0, 0, 100));


			
		}
	}
	



	CRadar::DrawBlips();
	m_bMapLoaded = true;


	//Loading Fade
	float fProgress = min(1.0f,(CTimer::m_snTimeInMillisecondsPauseMode - m_nMapTimer)/400.0f);
	int MyFadeAlpha = max(((pow(2, 8 * fProgress) - 1) / 255)*255,0);
	if (MyFadeAlpha > 0)
		CSprite2d::DrawRect(CRect::CRect(0, 0, RsGlobal.maximumWidth, RsGlobal.maximumHeight), CRGBA::CRGBA(95, 125, 148, (255 -MyFadeAlpha)));


	if (m_bMapLegend)
	{
		if (CRadar::MapLegendCounter > 9)
			CSprite2d::DrawRect(CRect::CRect(-1, StretchY(60.0f), StretchX(250.0f), RsGlobal.maximumHeight - StretchY(61.0f)), CRGBA::CRGBA(0, 0, 0, 150));
		else
			CSprite2d::DrawRect(CRect::CRect(-1, StretchY(60.0f), StretchX(150.0f), StretchY(80.0f) + StretchY(30 * CRadar::MapLegendCounter)), CRGBA::CRGBA(0, 0, 0, 150));

		for (int i = 0; i < CRadar::MapLegendCounter; i++)
		{
			if (i > 9)
				CRadar::DrawLegend(StretchX(120.0f), StretchY(80.0f) + StretchY(30 * i) - StretchY(30 * 10), CRadar::MapLegendList[i]);
			else
				CRadar::DrawLegend(StretchX(5.0f), StretchY(80.0f) + StretchY(30 * i), CRadar::MapLegendList[i]);
		}
	}
	DisplayHelperText("FEH_MPH");

	drawRadarOrMap = 0;
	return true;
}

char CMenuManager::DrawControllerSetupScreen()
{
	return	((char(__thiscall *)(CMenuManager*))0x57F300)(this);
}

char CMenuManager::PrintRadioStationList()
{
	return	((char(__thiscall *)(CMenuManager*))0x5746F0)(this);
}

void CMenuManager::DrawQuitGameScreen()
{
	((char(__thiscall *)(CMenuManager*))0x57D860)(this);
}

char CMenuManager::DrawStandardMenus(char DrawTitel)
{
	//return ((char(__thiscall *)(CMenuManager*, char))0x5794A0)(this, DrawTitel);

	// HEADER///
	CFont::SetBackground(0, 0);
	CFont::SetProp(1);
	CFont::SetAlignment(ALIGN_LEFT);
	CFont::SetWrapx((RsGlobal.maximumWidth - 10));
	CFont::SetRightJustifyWrap(10.0);
	CFont::SetCentreSize(RsGlobal.maximumWidth);
	if (m_nCurrentMenuPage == MENUPAGE_STATS)
		PrintStats();
	else if (m_nCurrentMenuPage == MENUPAGE_BRIEF)
		PrintBriefs();
	else if (m_nCurrentMenuPage == MENUPAGE_AUDIO_SETTINGS)
		PrintRadioStationList();
	DrawTitel = 0;
	if (DrawTitel && MenuPages[m_nCurrentMenuPage].m_szTitleName[0])
	{
		if (m_nCurrentMenuPage != MENUPAGE_MAP || !m_bMapLoaded)
		{
			CFont::SetAlignment(ALIGN_LEFT);
			CFont::SetFontStyle(FONT_PRICEDOWN);
			CFont::SetScale(StretchX(0.9), StretchY(0.9));
			CFont::SetOutlinePosition(1);
			CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
			CFont::SetDropColor(HudColour.GetRGB(HUD_COLOUR_BLACK, 255));
			CFont::PrintString(StretchX(28.0), StretchY(30.0), TheText.Get(MenuPages[m_nCurrentMenuPage].m_szTitleName));
		}
	}
	CSprite2d::DrawRect(CRect::CRect(StretchX(-1), StretchY(-1), RsGlobal.maximumWidth, StretchY(60)), CRGBA::CRGBA(0, 0, 0, 230));
	CSprite2d::DrawRect(CRect::CRect(-1, RsGlobal.maximumHeight - StretchY(60.0f), RsGlobal.maximumWidth, RsGlobal.maximumHeight), CRGBA::CRGBA(0, 0, 0, 230));
	//Main MEnu on Top//
	float MultRes = 1;
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetFontStyle(FONT_MENU);
	CFont::SetScale(StretchX(0.6), StretchY(0.65));
	float Resfac = ((float)RsGlobal.maximumWidth / (float)RsGlobal.maximumHeight);
	if (Resfac <= 1.63f)
	{
		CFont::SetScale(StretchX(0.45), StretchY(0.45));
		MultRes = 0.8;
		if (Resfac <= 1.5f)
			MultRes = 0.6;

	}
	
	CFont::SetOutlinePosition(1);
	CFont::SetDropColor(HudColour.GetRGB(HUD_COLOUR_BLACK, 255));

	if (m_bMainMenuSwitch)
		MyMainMenu.m_nActiveMenu = 1;
	else
		MyMainMenu.m_nActiveMenu = 0;

	for (int i = 0; i < 12; i++)
	{
		if (MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_szName[0])
		{
			if (MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_nTargetMenu == m_nCurrentMenuPage)
				CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_ORANGE, 255));
			else if (i == MyMainMenu.m_nHoverItem)
				CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
			else
				CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_GREY, 255));

			CFont::PrintString(StretchX(MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_wPosnX*MultRes),
				StretchY(MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_wPosnY),
				TheText.Get(MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_szName));

			if (i != 0)
				CSprite2d::DrawRect(CRect::CRect(StretchX(MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_wPosnX - 46.0)*MultRes, StretchY(45),
					StretchX(MyMainMenu.Menu[MyMainMenu.m_nActiveMenu].m_aButtons[i].m_wPosnX - 46.5)*MultRes, StretchY(60)), CRGBA::CRGBA(200, 200, 200, 100));

		}
	}


	//Actions///

//Questions//
	if (MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_nActionType == 1)
	{
		static char* pText;
		CFont::SetFontStyle(FONT_SUBTITLES);
		CFont::SetAlignment(ALIGN_LEFT);
		CFont::SetScale(StretchX(0.5f), StretchY(0.8f));
		CFont::SetOutlinePosition(1);
		CFont::SetColor(CRGBA(255, 255, 255, 255));
		CFont::SetDropColor(CRGBA(0, 0, 0, 255));

		switch (m_nCurrentMenuPage)
		{
		case MENUPAGE_NEW_GAME_ASK:
			pText = TheText.Get(m_bMainMenuSwitch ? "FESZ_QQ" : MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_szName);
			break;
		case MENUPAGE_LOAD_GAME_ASK:
			pText = TheText.Get(m_bMainMenuSwitch ? "FES_LCG" : MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_szName);
			break;
		case MENUPAGE_SAVE_WRITE_ASK:
		{
			if (m_bSelectedSaveGame)
				pText = TheText.Get(m_bSelectedSaveGame == 2 ? "FESZ_QC" : MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_szName);
			else
				pText = TheText.Get("FESZ_QO");
			break;
		}
		case MENUPAGE_QUIT_GAME_ASK:
			pText = TheText.Get("FEQ_SRW");
			break;
		default:
			pText = TheText.Get(MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_szName);
			break;
		}
		CFont::PrintString(RsGlobal.maximumWidth / 2 - StretchX(200), RsGlobal.maximumHeight / 2 - StretchY(80), pText);
	}



	for (int i = 0; i < 12; i++)
	{
		CFont::SetFontStyle(FONT_MENU);
		CFont::SetOutlinePosition(1);
		CFont::SetScale(StretchX(0.6f), StretchY(0.6f));
		CFont::SetAlignment(ALIGN_LEFT);
		if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nActionType != MENU_ACTION_TEXT && MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_szName[0])
		{
			const char* LeftColumn = nullptr;
			const char* RightColumn = nullptr;
			char ReservedSpace[64];

			if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nType >= MENU_ENTRY_SAVE_1 && MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nType <= MENU_ENTRY_SAVE_8)
			{
				if (*Slotvalidation[i] == 0)
					LeftColumn = plugin::CallAndReturn<const char*, 0x5D0F40>(i - 1);
				if (*Slotvalidation[i] == 2)
					LeftColumn = TheText.Get("FESZ_CS");

				if (!LeftColumn || !LeftColumn[0])
				{
					sprintf(gString, "FEM_SL%X", i);
					LeftColumn = TheText.Get(gString);
				}
			}
			else if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nType == MENU_ENTRY_MISSIONPACK)
			{

			}
			else if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nType == MENU_ENTRY_JOYMOUSE)
			{
				LeftColumn = TheText.Get(m_nController ? "FEJ_TIT" : "FEC_MOU");
			}
			else
			{
				LeftColumn = TheText.Get(MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_szName);
			}


			CAERadioTrackManager RadioEntity;

			switch (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nActionType) {
			case MENU_ACTION_RADIOEQ:
				RightColumn = TheText.Get(m_bRadioEq ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_RADIOAUTOTUNE:
				RightColumn = TheText.Get(m_bRadioAutoSelect ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_RADIOSTATION:
				RightColumn = RadioEntity.GetRadioStationName(m_nRadioStation);
				break;
			case MENU_ACTION_MAPLEGEND:
				RightColumn = TheText.Get(m_bMapLegend ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_SUBTITLE:
				RightColumn = TheText.Get(m_bShowSubtitles ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_WIDESCREEN:
				RightColumn = TheText.Get(m_bWidescreenOn ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_RADARMODE:
				switch (m_dwRadarMode) {
				case 0:
					RightColumn = TheText.Get("FED_RDM");
					break;
				case 1:
					RightColumn = TheText.Get("FED_RDB");
					break;
				case 2:
					RightColumn = TheText.Get("FEM_OFF");
					break;
				}
				break;
			case MENU_ACTION_HUD:
				switch (FrontEndMenuManager.m_bHudOn) {
				case 0:
					RightColumn = TheText.Get("FEM_OFF");
					m_dwRadarMode = 2;
					break;
				case 1:
					RightColumn = TheText.Get("FEM_ON");
					//m_dwRadarMode = 0;
					break;
				}
				break;
			case MENU_ACTION_SAVEGALLERYPHOTOS:
				RightColumn = TheText.Get(m_bSavePhotos ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_USERTRACKSPLAYMODE:
				switch (m_nRadioMode) {
				case 0:
					RightColumn = TheText.Get("FEA_PR1");
					break;
				case 1:
					RightColumn = TheText.Get("FEA_PR2");
					break;
				case 2:
					RightColumn = TheText.Get("FEA_PR3");
					break;
				}
				break;
			case MENU_ACTION_FRAMELIMIT:
				RightColumn = TheText.Get(m_bFrameLimiterOn ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_MIPMAPS:
				RightColumn = TheText.Get(m_bMipMapping ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_USERTRACKSAUTOMATICSCAN:
				RightColumn = TheText.Get(m_bTracksAutoScan ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_INVERTMOUSE:
				RightColumn = TheText.Get(!bInvertMouseY ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_INVERTLEFTSTICKX:
				RightColumn = TheText.Get(invertPadX1 ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_INVERTLEFTSTICKY:
				RightColumn = TheText.Get(invertPadY1 ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_INVERTRICHTSTICKX:
				RightColumn = TheText.Get(invertPadX2 ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_INVERTRIGHTSTICKY:
				RightColumn = TheText.Get(invertPadY2 ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_INVERTLEFTAXIS:
				RightColumn = TheText.Get(swapPadAxis1 ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_INVERTRIGHTAXIS:
				RightColumn = TheText.Get(swapPadAxis2 ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_STEERWITHMOUSE:
				RightColumn = TheText.Get(CVehicle::m_bEnableMouseSteering ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_FLYWITHMOUSE:
				RightColumn = TheText.Get(CVehicle::m_bEnableMouseFlying ? "FEM_ON" : "FEM_OFF");
				break;
			case MENU_ACTION_RESOLUTION:
			{
				//	const char* pszResolution = ((const char**(*)())0x745AF0)()[FrontEndMenuManager.m_dwResolution];
				char** Videomodes = FIND_VIDEOMODES();
				AsciiToGxtChar(Videomodes[m_dwResolution], ReservedSpace);
				/*if (!pszResolution)
					pszResolution = "";
*/
//strncpy(ReservedSpace, pszResolution, sizeof(ReservedSpace));
				RightColumn = ReservedSpace;
			}
			break;
			case MENU_ACTION_ANTIALIASING:
				if (m_dwAntiAliasingLevel <= 1)
					RightColumn = TheText.Get("FEM_OFF");
				else {
					switch (m_dwAntiAliasingLevel)
					{
					case 2:
						RightColumn = "2x";
						break;
					case 3:
						RightColumn = "4x";
						break;
					case 4:
						RightColumn = "8x";
						break;
					}
				}
				break;
			case MENU_ACTION_VISUALFX:
				switch (g_fx.GetFxQuality()) {
				case FXQUALITY_LOW:
					RightColumn = TheText.Get("FED_FXL");
					break;
				case FXQUALITY_MEDIUM:
					RightColumn = TheText.Get("FED_FXM");
					break;
				case FXQUALITY_HIGH:
					RightColumn = TheText.Get("FED_FXH");
					break;
				case FXQUALITY_VERY_HIGH:
					RightColumn = TheText.Get("FED_FXV");
					break;
				}
				break;
			case MENU_ACTION_CHANGEINPUTDEVICE:
				RightColumn = TheText.Get(FrontEndMenuManager.m_nController ? "FET_CCN" : "FET_SCN");
				break;
			}




			//Print left/Right
			if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_wPosnY == 0 && i > 0)
				MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_wPosnY = MenuPages[m_nCurrentMenuPage].m_aButtons[i - 1].m_wPosnY + 26;

			if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_wPosnX == 0)
				MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_wPosnX = MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_wPosnX;

			float PosX = StretchX(MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_wPosnX);
			float Posy = StretchY(MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_wPosnY);


			CFont::SetColor(CRGBA(255, 255, 255, 255));
			if (i == m_dwSelectedMenuItem)
			{
				CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_ORANGE, 255));
				//CSprite2d::DrawRect(CRect::CRect(StretchX(50), Posy - StretchY(5), RsGlobal.maximumWidth - StretchX(50), Posy + StretchY(15)), CRGBA::CRGBA(100, 100, 100, 150));
			}
			// Print left column
			CFont::SetDropColor(CRGBA(0, 0, 0, 255));

			CFont::SetOutlinePosition(ALIGN_LEFT);

			//if (FrontEndMenuManager.m_nCurrentMenuPage == 0)
			//	CFont::PrintString(fPosnXForStats, Posy, (char*)LeftColumn);
			//else
			CFont::PrintString(PosX, Posy, (char*)LeftColumn);


			// Print right column
			if (RightColumn) {
				float width = CFont::GetStringWidth((char*)RightColumn, true, false);
				CFont::SetOutlinePosition(1);
				CFont::SetScale(StretchX(0.6f), StretchY(0.6f));
				if (width > StretchX(200.0f))
					CFont::SetScale(StretchX(0.6f *  StretchX(200.0f) / width), StretchY(0.6f));

				CFont::SetOutlinePosition(ALIGN_LEFT);
				CFont::PrintString(RsGlobal.maximumWidth - StretchX(300), Posy, (char*)RightColumn);
			}



			float SliderPosX = RsGlobal.maximumWidth - StretchX(300);
			float SliderPosY = Posy + StretchY(7.0f);
			float SliderWidth = StretchX(150.0f);
			float Sliderheight = StretchY(5.0f);
			float Sliderfield = 0.0f;
			switch (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nActionType)
			{
			case MENU_ACTION_SLIDER_BRIGHTNESS:
			{
				Sliderfield = DisplaySlider(SliderPosX, SliderPosY, Sliderheight, Sliderheight, SliderWidth, m_dwBrightness * 0.0026041667f, true);
				if (i == m_dwSelectedMenuItem)
				{
					if (CheckHover(0, Sliderfield - StretchX(4.0f), SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_BRIGHTNESSNEGATIV;
					else if (CheckHover(Sliderfield + StretchX(4.0f), RsGlobal.maximumWidth, SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_BRIGHTNESSPLUS;
					else
						bSlidingType = SLIDINGTYPE_STATIC;
				}
				break;
			}

			case MENU_ACTION_SLIDER_MUSIC:
			{
				Sliderfield = DisplaySlider(SliderPosX, SliderPosY, Sliderheight, Sliderheight, SliderWidth, m_nRadioVolume * 0.015625, true);
				if (i == m_dwSelectedMenuItem)
				{
					if (CheckHover(0, Sliderfield - StretchX(4.0f), SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_RADIONEGATIV;
					else if (CheckHover(Sliderfield + StretchX(4.0f), RsGlobal.maximumWidth, SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_RADIOPLUS;
					else
						bSlidingType = SLIDINGTYPE_STATIC;
				}
				break;
			}

			case MENU_ACTION_SLIDER_SFX:
			{
				Sliderfield = DisplaySlider(SliderPosX, SliderPosY, Sliderheight, Sliderheight, SliderWidth, m_nSfxVolume * 0.015625, true);
				if (i == m_dwSelectedMenuItem)
				{
					if (CheckHover(0, Sliderfield - StretchX(4.0f), SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_SFXNEGATIV;
					else if (CheckHover(Sliderfield + StretchX(4.0f), RsGlobal.maximumWidth, SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_SFXPLUS;
					else
						bSlidingType = SLIDINGTYPE_STATIC;
				}
				break;
			}

			case MENU_ACTION_SLIDER_LOD:
			{
				Sliderfield = DisplaySlider(SliderPosX, SliderPosY, Sliderheight, Sliderheight, SliderWidth, (m_fDrawDistance - 0.92500001) * 1.1428572, true);
				if (i == m_dwSelectedMenuItem)
				{
					if (CheckHover(0, Sliderfield - StretchX(4.0f), SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_DRAWDISTANCENEGATIV;
					else if (CheckHover(Sliderfield + StretchX(4.0f), RsGlobal.maximumWidth, SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_DRAWDISTANCEPLUS;
					else
						bSlidingType = SLIDINGTYPE_STATIC;
				}
				break;
			}

			case MENU_ACTION_SLIDER_MOUSESENSITIVITY:
			{
				Sliderfield = DisplaySlider(SliderPosX, SliderPosY, Sliderheight, Sliderheight, SliderWidth, CCamera::m_fMouseAccelHorzntl / 0.0049999999, true);
				if (i == m_dwSelectedMenuItem)
				{
					if (CheckHover(0, Sliderfield - StretchX(4.0f), SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_MOUSEACCLNEGATIV;
					else if (CheckHover(Sliderfield + StretchX(4.0f), RsGlobal.maximumWidth, SliderPosY - Sliderheight, SliderPosY + Sliderheight))
						bSlidingType = SLIDINGTYPE_MOUSEACCLPLUS;
					else
						bSlidingType = SLIDINGTYPE_STATIC;
				}
				break;
			}

			default:
				break;
			}

		}


	}

	return 1;
}

void CMenuManager::DrawFrontEnd()
{
	if (!m_bDontDrawFrontEnd)
	{
		CFont::SetAlphaFade(255.0);
		CSprite2d::InitPerFrame();
		CFont::InitPerFrame();
		DefinedState2d();
		SetFrontendRenderStates();
		m_bAudioRetuneInProgress = 1;
		if (AudioEngine.IsRadioRetuneinProgress())
			m_bAudioRetuneInProgress = 0;

		//Show Menupage Map as first page when the game is already running 
		if (m_nCurrentMenuPage == MENUPAGE_QUIT_GAME_2)
			m_nCurrentMenuPage = m_bMainMenuSwitch == 0 ? MENUPAGE_MAP : MENUPAGE_MAIN_MENU;
		if (!m_dwSelectedMenuItem && MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_nActionType == 1)
			m_dwSelectedMenuItem = 1;
		CMenuManager::DrawBackground();
	}
}

char CMenuManager::SmallMessageScreen(char* Key)
{
	return ((char(__thiscall *)(CMenuManager*, char*))0x574010)(this, Key);
}

void CMenuManager::ResetHelperText()
{
	((void(__thiscall *)(CMenuManager*))0x57CD30)(this);
}

int CMenuManager::SetHelperText(int a2)
{
	return ((int(__thiscall *)(CMenuManager*, int))0x57CD10)(this, a2);
}

void CMenuManager::SetFrontendRenderStates()
{
	((void(__cdecl *)())0x573A60)();
}

char CMenuManager::DisplayHelperText(char * text)
{
	return ((char(__thiscall *)(CMenuManager*, char*))0x57E240)(this, text);
}

int CMenuManager::DisplaySlider(float x, float y, float Height, float Height2, float Width, float progress, signed int rgbaColor)
{
	float PosLeft = x;
	float PosRight = x + Width;
	float PosRightProgress = x + Width * progress;
	float PosTop = y + Height2 / 2 - 2 * Height;
	float PosBottom = PosTop + 2 * Height;

	// Draw Black background (as border)
	CRect BackgroundRectBorder = CRect(PosLeft - StretchX(1.0f), PosTop - StretchY(1.0f), PosRight + StretchX(1.0f), PosBottom + StretchY(1.0f));
	CSprite2d::DrawRect(BackgroundRectBorder, CRGBA::CRGBA(10, 10, 10, 255));

	//Draw real gray background
	CRect BackgroundRect = CRect(PosLeft, PosTop, PosRight, PosBottom);
	CSprite2d::DrawRect(BackgroundRect, CRGBA::CRGBA(100, 100, 100, 255));

	//Draw current Progress/Slider
	CRect Rect = CRect(PosLeft, PosTop, PosRightProgress, PosBottom);
	CSprite2d::DrawRect(Rect, CRGBA::CRGBA(240, 240, 240, 240));

	// Draw an slider knob
	float SizeXKnob = StretchX(2.0f);
	float OverSizeYKnob = StretchY(0.0f);
	CRect CurrentPosRect = CRect(PosRightProgress - SizeXKnob, PosTop - OverSizeYKnob, PosRightProgress + SizeXKnob, PosBottom + OverSizeYKnob);
	CSprite2d::DrawRect(CurrentPosRect, CRGBA::CRGBA(20, 20, 20, 255));

	return x + Width * progress + StretchX(2.0f);
}

void CMenuManager::DefinedState2d()
{
	((char(__thiscall *)(CMenuManager*))0x734750)(this);
}

bool CMenuManager::CheckHover(int left, int right, int bottom, int top)
{
	return ((bool(__thiscall *)(CMenuManager*, int, int, int, int))0x57C4F0)(this, left, right, bottom, top);
}

char CMenuManager::PrintStats()
{
	return ((char(__thiscall *)(CMenuManager *))0x574900)(this);
}

char CMenuManager::PrintBriefs()
{
	return ((char(__thiscall *)(CMenuManager *))0x576320)(this);
}


void CMenuManager::SaveSettings() {
    plugin::CallMethod<0x57C660, CMenuManager *>(this);
}



void CMenuManager::MyInit()
{
	MemoryVP::InjectHook(0x576860, &CMenuManager::DisplaySlider, PATCH_JUMP);
	MemoryVP::InjectHook(0x57B750, &CMenuManager::DrawBackground, PATCH_JUMP);
	MemoryVP::InjectHook(0x5794A0, &CMenuManager::DrawStandardMenus, PATCH_JUMP);
	MemoryVP::InjectHook(0x5744D0, &CMenuManager::Initialise, PATCH_JUMP);
	MemoryVP::InjectHook(0x57C290, &CMenuManager::DrawFrontEnd, PATCH_JUMP);
	//MemoryVP::InjectHook(0x575130, &CMenuManager::PrintMap, PATCH_JUMP);
	//Patch Call because the old one still exists and is called inside the fucntion.
	MemoryVP::InjectHook(0x57B457, &CMenuManager::UserInput, PATCH_CALL);
	MemoryVP::Patch<char>(0x57FE9C, 0x14); //Distance between Menubuttons in Userinput


	//Initial Mapzoom on Menu opening.
	MemoryVP::Patch<float>(0x57453A + 3, 270.0f);
	MemoryVP::Patch<float>(0x5779F7 + 3, 270.0f);



	int i = 0;
	int posx = 50.0f;
	int xoffset = 100.0f;
	MyMainMenu.Menu[0].m_aButtons[i].m_nTargetMenu = MENUPAGE_MAP;
	MyMainMenu.Menu[0].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[0].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[0].m_aButtons[i].m_szName, "FEH_MAP", sizeof("FEH_MAP"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[0].m_aButtons[i].m_nTargetMenu = MENUPAGE_BRIEF;
	MyMainMenu.Menu[0].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[0].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[0].m_aButtons[i].m_szName, "FEH_BRI", sizeof("FEH_BRI"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[0].m_aButtons[i].m_nTargetMenu = MENUPAGE_CONTROLLER_SETUP;
	MyMainMenu.Menu[0].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[0].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[0].m_aButtons[i].m_szName, "FEO_CON", sizeof("FEO_CON"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[0].m_aButtons[i].m_nTargetMenu = MENUPAGE_DISPLAY_SETTINGS;
	MyMainMenu.Menu[0].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[0].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[0].m_aButtons[i].m_szName, "FEO_DIS", sizeof("FEO_DIS"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[0].m_aButtons[i].m_nTargetMenu = MENUPAGE_DISPLAY_ADVANCED;
	MyMainMenu.Menu[0].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[0].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[0].m_aButtons[i].m_szName, "FED_ADV", sizeof("FED_ADV"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[0].m_aButtons[i].m_nTargetMenu = MENUPAGE_AUDIO_SETTINGS;
	MyMainMenu.Menu[0].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[0].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[0].m_aButtons[i].m_szName, "FEO_AUD", sizeof("FEO_AUD"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[0].m_aButtons[i].m_nTargetMenu = MENUPAGE_START_GAME;
	MyMainMenu.Menu[0].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[0].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[0].m_aButtons[i].m_szName, "FEH_LOA", sizeof("FEH_LOA"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[0].m_aButtons[i].m_nTargetMenu = MENUPAGE_QUIT_GAME_ASK;
	MyMainMenu.Menu[0].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[0].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[0].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[0].m_aButtons[i].m_szName, "FEP_QUI", sizeof("FEP_QUI"));

	i = 0;
	posx = 50.0f;
	MyMainMenu.Menu[1].m_aButtons[i].m_nTargetMenu = MENUPAGE_CONTROLLER_SETUP;
	MyMainMenu.Menu[1].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[1].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[1].m_aButtons[i].m_szName, "FEO_CON", sizeof("FEO_CON"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[1].m_aButtons[i].m_nTargetMenu = MENUPAGE_DISPLAY_SETTINGS;
	MyMainMenu.Menu[1].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[1].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[1].m_aButtons[i].m_szName, "FEO_DIS", sizeof("FEO_DIS"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[1].m_aButtons[i].m_nTargetMenu = MENUPAGE_DISPLAY_ADVANCED;
	MyMainMenu.Menu[1].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[1].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[1].m_aButtons[i].m_szName, "FED_ADV", sizeof("FED_ADV"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[1].m_aButtons[i].m_nTargetMenu = MENUPAGE_AUDIO_SETTINGS;
	MyMainMenu.Menu[1].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[1].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[1].m_aButtons[i].m_szName, "FEO_AUD", sizeof("FEO_AUD"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[1].m_aButtons[i].m_nTargetMenu = MENUPAGE_START_GAME;
	MyMainMenu.Menu[1].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[1].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[1].m_aButtons[i].m_szName, "FEH_LOA", sizeof("FEH_LOA"));

	i++;
	posx = posx + xoffset;
	MyMainMenu.Menu[1].m_aButtons[i].m_nTargetMenu = MENUPAGE_QUIT_GAME_ASK;
	MyMainMenu.Menu[1].m_aButtons[i].m_nAlign = ALIGN_CENTER;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnX = posx;
	MyMainMenu.Menu[1].m_aButtons[i].m_wPosnY = 40.0f;
	MyMainMenu.Menu[1].m_aButtons[i].m_nType = MENU_ENTRY_BUTTON;
	strncpy(MyMainMenu.Menu[1].m_aButtons[i].m_szName, "FEP_QUI", sizeof("FEP_QUI"));


}



